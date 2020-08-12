#include "Timer.h"
#include "TimerImpl.hxx"
#include "BassCommon.h"

Bass::Timer::Timer()
{
	m_pImpl = new TimerImpl();
}

Bass::Timer::~Timer()
{
	SafeDelete(m_pImpl);
}

void Bass::Timer::Start()
{
	if (nullptr != m_pImpl)
		m_pImpl->Start();
}

bool Bass::Timer::AddAlarm(const ETimerType& type, const std::tm& time, std::function<void()> fn)
{
	if (nullptr == m_pImpl)
		return false;

	return m_pImpl->AddAlarm(type, time, fn);
}
