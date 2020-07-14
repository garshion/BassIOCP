#include "UDPSender.h"
#include "UDPSenderImpl.hxx"

Bass::UDPSender::UDPSender(const char* strHost, int nPort)
{
	m_pSender = new UDPSenderImpl(strHost, nPort);
}

Bass::UDPSender::~UDPSender()
{
	SafeDelete(m_pSender);
}

void Bass::UDPSender::Send(char* pBuffer, int nBufferSize)
{
	if (nullptr != m_pSender)
		m_pSender->Send(pBuffer, nBufferSize);
}

void Bass::UDPSender::Send(char* pBuffer, int nBufferSize, const std::string& strHost, int nPort)
{
	if (nullptr != m_pSender)
		m_pSender->Send(pBuffer, nBufferSize, strHost, nPort);
}
