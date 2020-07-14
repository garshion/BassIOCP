#include "UDPSenderImpl.hxx"

Bass::UDPSenderImpl::UDPSenderImpl(const char * strHost, int nPort)
{
	m_strLastSendHost = strHost;

	if (nPort <= 0
		|| nPort >= 0x10000)
		m_nLastPort = 0;
	else
		m_nLastPort = (unsigned short)nPort;
	m_Socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

	_MakeAddr();
}
Bass::UDPSenderImpl::~UDPSenderImpl()
{
	if (INVALID_SOCKET != m_Socket)
	{
		shutdown(m_Socket, SD_BOTH);
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
	}
}

void Bass::UDPSenderImpl::Send(char * pBuffer, int nBufferSize)
{
	if (nullptr == pBuffer
		|| nBufferSize <= 0)
		return;

	if (INVALID_SOCKET == m_Socket)
		return;

	sendto(m_Socket, pBuffer, nBufferSize, 0, (sockaddr*)&m_Addr, m_nAddrSize);
}

void Bass::UDPSenderImpl::Send(char * pBuffer, int nBufferSize, const std::string & strHost, int nPort)
{
	if (true == strHost.empty()
		|| nPort <= 0
		|| nPort >= 0x10000)
		return;

	m_strLastSendHost = strHost;
	m_nLastPort = (unsigned short)nPort;

	_MakeAddr();
	Send(pBuffer, nBufferSize);
}

void Bass::UDPSenderImpl::_MakeAddr()
{
	m_Addr.sin_family = AF_INET;
	inet_pton(AF_INET, m_strLastSendHost.c_str(), &m_Addr.sin_addr.s_addr);
	m_Addr.sin_port = htons(m_nLastPort);
}
