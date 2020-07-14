#include "StopWatchImpl.hxx"
#include <chrono>

Bass::StopWatchImpl::StopWatchImpl()
{
}

Bass::StopWatchImpl::~StopWatchImpl()
{
}

bool Bass::StopWatchImpl::Start()
{
	if (true == m_setStart)
		return false;
	m_StartTime = std::chrono::system_clock::now();
	m_setStart = true;
	m_setEnd = false;

	return true;
}

bool Bass::StopWatchImpl::Stop()
{
	if (false == m_setStart)
		return false;

	m_EndTime = std::chrono::system_clock::now();
	m_setEnd = true;
	return true;
}

void Bass::StopWatchImpl::Reset()
{
	m_setStart = m_setEnd = false;
}

double Bass::StopWatchImpl::GetSeconds() const
{
	if (false == m_setEnd)
		return 0.0;

	return std::chrono::duration<double>(m_EndTime - m_StartTime).count();
}

long long Bass::StopWatchImpl::GetMilliseconds() const
{
	return GetNanoseconds() / 1000000;
}

long long Bass::StopWatchImpl::GetNanoseconds() const
{
	if (false == m_setEnd)
		return 0;

	return std::chrono::nanoseconds(m_EndTime - m_StartTime).count();
}

