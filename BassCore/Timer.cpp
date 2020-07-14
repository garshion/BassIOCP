#include "Timer.h"
#include "BassCommon.h"

Bass::Timer::Timer(bool bUseSystemClock)
{
	m_bUseSystemClock = bUseSystemClock;
	_Initialize();

	m_IsRunning = true;
	m_pThread = new std::thread(&Timer::_Process, this);
	m_pThread->detach();
}

Bass::Timer::~Timer()
{
	_Release();
}

bool Bass::Timer::AddTimerEvent(OnTimerFunc pEvent, ETimerType type)
{
	if (nullptr == pEvent)
		return false;

	auto it = m_mapTimerEvent.find(pEvent);
	if (m_mapTimerEvent.end() != it)
		return false;

	AutoLock(m_Lock);

	switch (type)
	{
	case TIMER_TYPE_SECOND:
		m_vecSec.push_back(pEvent);
		break;
	case TIMER_TYPE_MINUTE:
		m_vecMin.push_back(pEvent);
		break;
	case TIMER_TYPE_HOUR:
		m_vecHour.push_back(pEvent);
		break;
	case TIMER_TYPE_DAY:
		m_vecDay.push_back(pEvent);
		break;
	default:
		return false;
	}

	m_mapTimerEvent.insert(std::make_pair(pEvent, type));

	return true;
}

void Bass::Timer::RemoveTimerEvent(OnTimerFunc pEvent)
{
	auto it = m_mapTimerEvent.find(pEvent);
	if (m_mapTimerEvent.end() == it)
		return;

	vecOnTimer_t* pList = nullptr;
	switch (it->second)
	{
	case TIMER_TYPE_SECOND: pList = &m_vecSec; break;
	case TIMER_TYPE_MINUTE: pList = &m_vecMin; break;
	case TIMER_TYPE_HOUR: pList = &m_vecHour; break;
	case TIMER_TYPE_DAY: pList = &m_vecDay; break;
	default:
		return;
	}

	AutoLock(m_Lock);

	for (auto itr = pList->begin(); itr != pList->end(); ++itr)
	{
		if (pEvent == *itr)
		{
			pList->erase(itr);
			break;
		}
	}

	m_mapTimerEvent.erase(it);
}

void Bass::Timer::_Process()
{
	auto nextTime = m_BaseTime + sec_t(0.0);
	std::this_thread::sleep_until(nextTime);

	while (true == m_IsRunning)
	{
		nextTime += sec_t(1.0);
		m_nBaseTimeCount = (++m_nBaseTimeCount % DAY_PER_SECONDS);

		_OnSecond();
		if (0 == (m_nBaseTimeCount % MINUTE_PER_SECONDS))
			_OnMinute();
		if (0 == (m_nBaseTimeCount % HOUR_PER_SECONDS))
			_OnHour();
		if (0 == (m_nBaseTimeCount % DAY_PER_SECONDS))
			_OnDay();

		std::this_thread::sleep_until(nextTime);
	}
}

void Bass::Timer::_OnEvent(ETimerType type)
{
	if (false == m_IsRunning)
		return;


	vecOnTimer_t* pList = nullptr;

	switch (type)
	{
	case TIMER_TYPE_SECOND:
		pList = &m_vecSec;
		break;
	case TIMER_TYPE_MINUTE:
		pList = &m_vecMin;
		break;
	case TIMER_TYPE_HOUR:
		pList = &m_vecHour;
		break;
	case TIMER_TYPE_DAY:
		pList = &m_vecDay;
		break;
	default:
		return;
	}

	AutoLock(m_Lock);

	for (auto func : *pList)
	{
		if (nullptr != func)
			func();
	}
}

void Bass::Timer::_OnSecond()
{
	_OnEvent(TIMER_TYPE_SECOND);
}

void Bass::Timer::_OnMinute()
{
	_OnEvent(TIMER_TYPE_MINUTE);
}

void Bass::Timer::_OnHour()
{
	_OnEvent(TIMER_TYPE_HOUR);
}

void Bass::Timer::_OnDay()
{
	_OnEvent(TIMER_TYPE_DAY);
}

void Bass::Timer::_Initialize()
{
	m_BaseTime = CurrentTime();
	if (false == m_bUseSystemClock)
		return;

	time_t adjustTime = std::chrono::system_clock::to_time_t(m_BaseTime) + 2;
	m_nBaseTimeCount = adjustTime % DAY_PER_SECONDS;
	m_BaseTime = std::chrono::system_clock::from_time_t(adjustTime);
}

void Bass::Timer::_Release()
{
	m_IsRunning = false;
	SafeDelete(m_pThread);

	AutoLock(m_Lock);
	m_mapTimerEvent.clear();
	m_vecSec.clear();
	m_vecHour.clear();
	m_vecMin.clear();
	m_vecDay.clear();
}
