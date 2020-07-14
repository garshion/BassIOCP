#include "StopWatch.h"

Bass::StopWatch::StopWatch()
{
}

Bass::StopWatch::~StopWatch()
{
}

bool Bass::StopWatch::Start()
{
	if (true == m_setStart)
		return false;
	m_StartTime = CurrentTime();
	m_setStart = true;
	m_setEnd = false;

	return true;
}

bool Bass::StopWatch::Stop()
{
	if (false == m_setStart)
		return false;

	m_EndTime = CurrentTime();
	m_setEnd = true;
	return true;
}

void Bass::StopWatch::Reset()
{
	m_setStart = m_setEnd = false;
}

double Bass::StopWatch::GetSeconds() const
{
	if (false == m_setEnd)
		return 0.0;

	return sec_t(m_EndTime - m_StartTime).count();
}

long long Bass::StopWatch::GetMilliseconds() const
{
	return GetNanoseconds() / 1000;
}

long long Bass::StopWatch::GetNanoseconds() const
{
	if (false == m_setEnd)
		return 0;

	return ns_t(m_EndTime - m_StartTime).count();
}
