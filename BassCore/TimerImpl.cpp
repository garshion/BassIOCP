#include "TimerImpl.hxx"
#include <thread>
#include "BassCommon.h"

Bass::TimerData::TimerData()
{ 
	memset(&m_TimeData, 0x00, sizeof(std::tm));
}

Bass::TimerData::~TimerData()
{
}

void Bass::TimerData::RegisterFunc(const std::function<void()>& func)
{
	if (nullptr != func)
		m_fnTimer = func;
}

void Bass::TimerData::SetAlarmData(const ETimerType& type, const int& year, const int& month, const int& day, const int& hour, const int& min, const int& sec)
{
	SetAlarmType(type);
	SetYear(year);
	SetMonth(month);
	SetDay(day);
	SetHour(hour);
	SetMin(min);
	SetSec(sec);
}

void Bass::TimerData::SetAlarmType(const ETimerType& type)
{
	m_eTimerType = type;
}

void Bass::TimerData::SetYear(const int& year)
{
	m_TimeData.tm_year = year;
}

void Bass::TimerData::SetMonth(const int& month)
{
	m_TimeData.tm_mon = month;
}

void Bass::TimerData::SetDay(const int& day)
{
	m_TimeData.tm_mday = day;
}

void Bass::TimerData::SetDayOfWeek(const EDayOfWeek& day)
{
	if (m_eTimerType != ETimerType::EACH_DAY_OF_WEEK)
		return;

	switch (day)
	{
	case EDayOfWeek::Sunday:
	case EDayOfWeek::Monday:
	case EDayOfWeek::Tuesday:
	case EDayOfWeek::Wednesday:
	case EDayOfWeek::Thursday:
	case EDayOfWeek::Friday:
	case EDayOfWeek::Saturday:
	{
		m_nSetCount = (int)day;
	}
	break;

	default:
		break;
	}
}

void Bass::TimerData::SetHour(const int& hour)
{
	m_TimeData.tm_hour = hour;
}

void Bass::TimerData::SetMin(const int& min)
{
	m_TimeData.tm_min = min;
}

void Bass::TimerData::SetSec(const int& sec)
{
	m_TimeData.tm_sec = sec;
}

void Bass::TimerData::Update(const std::tm& time)
{
	switch (m_eTimerType)
	{
	case ETimerType::EVERY_SECOND:
	case ETimerType::EVERY_MINUTE:
	case ETimerType::EVERY_HOUR:
		_CheckEvery(time);
		break;
	case ETimerType::EACH_SECOND:
	case ETimerType::EACH_MINUTE:
	case ETimerType::EACH_HOUR:
	case ETimerType::EACH_DAY_OF_WEEK:
	case ETimerType::EACH_DAY:
		_CheckEach(time);
		break;
	case ETimerType::ONCE:
		_CheckOnce(time);
		break;
	default:
		break;
	}
}

const bool& Bass::TimerData::IsExpired() const
{
	return m_isExpired;
}

void Bass::TimerData::_SendAlarm()
{
	if (nullptr != m_fnTimer)
		m_fnTimer();
}

void Bass::TimerData::_CheckEvery(const std::tm& time)
{
	switch (m_eTimerType)
	{
	case ETimerType::EVERY_SECOND:
	{
		m_nCurrentCount = (m_nCurrentCount + 1) % m_nSetCount;
		if (0 == m_nCurrentCount)
			_SendAlarm();
	}
	break;
	case ETimerType::EVERY_MINUTE:
	{
		if (time.tm_sec == 0)
		{
			m_nCurrentCount = (m_nCurrentCount + 1) % m_nSetCount;
			if (0 == m_nCurrentCount)
				_SendAlarm();
		}
	}
	break;
	case ETimerType::EVERY_HOUR:
	{
		if (time.tm_sec == 0
			&& time.tm_min == 0)
		{
			m_nCurrentCount = (m_nCurrentCount + 1) % m_nSetCount;
			if (0 == m_nCurrentCount)
				_SendAlarm();
		}
	}
	break;
	default:
		break;
	}
}

void Bass::TimerData::_CheckEach(const std::tm& time)
{
	switch (m_eTimerType)
	{
	case ETimerType::EACH_SECOND:
	{
		if (time.tm_sec == m_TimeData.tm_sec)
			_SendAlarm();
	}
	break;
	case ETimerType::EACH_MINUTE:
	{
		if (time.tm_sec == m_TimeData.tm_sec
			&& time.tm_min == m_TimeData.tm_min)
			_SendAlarm();
	}
	break;
	case ETimerType::EACH_HOUR:
	{
		if (time.tm_sec == m_TimeData.tm_sec
			&& time.tm_min == m_TimeData.tm_min
			&& time.tm_hour == m_TimeData.tm_hour)
			_SendAlarm();
	}
	break;
	case ETimerType::EACH_DAY_OF_WEEK:
	{
		if (time.tm_sec == m_TimeData.tm_sec
			&& time.tm_min == m_TimeData.tm_min
			&& time.tm_hour == m_TimeData.tm_hour
			&& time.tm_wday == m_nSetCount)
			_SendAlarm();
	}
	break;
	case ETimerType::EACH_DAY:
	{
		if (time.tm_sec == m_TimeData.tm_sec
			&& time.tm_min == m_TimeData.tm_min
			&& time.tm_hour == m_TimeData.tm_hour
			&& time.tm_mday == m_TimeData.tm_mday)
			_SendAlarm();
	}
	break;
	default:
		break;
	}
}

void Bass::TimerData::_CheckOnce(const std::tm& time)
{
	if (m_eTimerType != ETimerType::ONCE)
		return;

	if (true == m_isExpired)
		return;

	if (time.tm_sec == m_TimeData.tm_sec
		&& time.tm_min== m_TimeData.tm_min
		&& time.tm_hour == m_TimeData.tm_hour
		&& time.tm_mday == m_TimeData.tm_mday
		&& time.tm_mon == m_TimeData.tm_mon
		&& time.tm_year == m_TimeData.tm_year)
	{
		_SendAlarm();
		m_isExpired = true;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////
// TimerImpl



Bass::TimerImpl::TimerImpl()
{
}

Bass::TimerImpl::~TimerImpl()
{
	m_IsStarted = false;
	std::this_thread::sleep_for(std::chrono::duration<double>(2.0));

	for (auto it = m_vecAlarmData.begin(); it != m_vecAlarmData.end(); ++it)
	{
		SafeDelete(*it);
	}
	m_vecAlarmData.clear();

	SafeDelete(m_pThread);
}

void Bass::TimerImpl::Start()
{
	if (true == m_IsStarted)
		return;

	m_IsStarted = true;

	m_pThread = new std::thread(&TimerImpl::_Process, this);
	m_pThread->detach();
}

bool Bass::TimerImpl::AddAlarm(const ETimerType& type, const std::tm& time, std::function<void()> fn)
{
	if (nullptr == fn)
		return false;

	TimerData* pData = new TimerData();
	pData->SetAlarmData(type, time.tm_year, time.tm_mon, time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);
	pData->RegisterFunc(fn);

	m_vecAlarmData.push_back(pData);
	return true;
}

void Bass::TimerImpl::_Process()
{
	auto tSleepTime = std::chrono::system_clock::now();

	// 정확한 초 맞추기
	auto tNanoVal = tSleepTime.time_since_epoch().count();
	auto nDelayTime = ((2 * SEC_NANO_VAL) - (tNanoVal % SEC_NANO_VAL));

	tSleepTime += std::chrono::system_clock::duration(nDelayTime);
	std::this_thread::sleep_until(tSleepTime);
	// end, 정확한 초 맞추기

	time_t nCurrentTime = 0;
	std::tm tmCurrentTime;
	while (true == m_IsStarted)
	{
		nCurrentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		localtime_s(&tmCurrentTime, &nCurrentTime);

		for (auto it = m_vecAlarmData.begin(); it != m_vecAlarmData.end();)
		{
			if (*it != nullptr
				&& false == (*it)->IsExpired())
			{
				(*it)->Update(tmCurrentTime);
				++it;
			}
			else
			{
				SafeDelete(*it);
				it = m_vecAlarmData.erase(it);
			}
		}

		tSleepTime += std::chrono::system_clock::duration(SEC_NANO_VAL);
		std::this_thread::sleep_until(tSleepTime);
	}

}
