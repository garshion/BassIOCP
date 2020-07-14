#include "StopWatch.h"
#include "StopWatchImpl.hxx"
#include "BassCommon.h"

Bass::StopWatch::StopWatch()
{
	m_pImpl = new StopWatchImpl();
}

Bass::StopWatch::~StopWatch()
{
	SafeDelete(m_pImpl);
}

bool Bass::StopWatch::Start()
{
	if (nullptr == m_pImpl)
		return false;
	return m_pImpl->Start();
}

bool Bass::StopWatch::Stop()
{
	if (nullptr == m_pImpl)
		return false;
	return m_pImpl->Stop();
}

void Bass::StopWatch::Reset()
{
	if (nullptr != m_pImpl)
		m_pImpl->Reset();
}

double Bass::StopWatch::GetSeconds() const
{
	if (nullptr == m_pImpl)
		return 0.0;
	return m_pImpl->GetSeconds();
}

int64_t Bass::StopWatch::GetMilliseconds() const
{
	if (nullptr == m_pImpl)
		return 0;
	return m_pImpl->GetMilliseconds();
}

int64_t Bass::StopWatch::GetNanoseconds() const
{
	if (nullptr == m_pImpl)
		return 0;
	return m_pImpl->GetNanoseconds();
}
