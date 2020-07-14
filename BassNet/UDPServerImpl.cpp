#include "UDPServerImpl.hxx"

Bass::UDPServerImpl::UDPServerImpl()
{
	memset(&m_addr, 0x00, sizeof(sockaddr_in));
}

Bass::UDPServerImpl::~UDPServerImpl()
{
	_Destroy();
}

bool Bass::UDPServerImpl::SetListenPort(int nPort)
{
	if (nPort <= 0
		|| nPort >= 0x10000)
		return false;

	if (m_Socket != INVALID_SOCKET)
		return false;

	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (m_Socket == INVALID_SOCKET)
		return false;

	unsigned short nSetPort = (unsigned short)nPort;

	memset(&m_addr, 0x00, sizeof(sockaddr_in));
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = INADDR_ANY;
	m_addr.sin_port = (htons(nSetPort));

	if (-1 == bind(m_Socket, (sockaddr*)&m_addr, sizeof(sockaddr_in)))
	{
		_Destroy();
		return false;
	}

	return true;
}

void Bass::UDPServerImpl::Start()
{
	if (true == m_isRunning)
		return;

	SafeDelete(m_pThread);
	m_isRunning = true;
	m_pThread = new std::thread(&Bass::UDPServerImpl::_Process, this);
	m_pThread->detach();
}

void Bass::UDPServerImpl::Stop()
{
	m_isRunning = false;

	if (INVALID_SOCKET != m_Socket)
	{
		shutdown(m_Socket, SD_BOTH);
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
	}
}

void Bass::UDPServerImpl::GetReceivedPacket(std::vector<Packet>& o_vecPacket)
{
	AutoLock(m_Lock);
	o_vecPacket.insert(o_vecPacket.end(), m_vecReceivedPacket.begin(), m_vecReceivedPacket.end());
}

int Bass::UDPServerImpl::_Receive(char * pBuffer, int nBufferSize)
{
	if (nullptr == pBuffer
		|| 0 == nBufferSize)
		return -1;

	if (m_Socket == INVALID_SOCKET)
		return -2;

	memset(&m_addr, 0x00, sizeof(sockaddr_in));
	return recvfrom(m_Socket, pBuffer, nBufferSize, 0, (sockaddr*)&m_addr, &m_nAddrSize);
}



void Bass::UDPServerImpl::_Process()
{
	char pBuffer[MAX_BUFFER_SIZE] = { 0, };

	while (true == m_isRunning)
	{
		int nReceiveSize = _Receive(pBuffer, MAX_BUFFER_SIZE);
		int nTotalUsed = 0;
		while (nReceiveSize > 0)
		{
			int nUsed = 0;
			if (false == m_Resolver.Resolve(pBuffer + nTotalUsed, nReceiveSize, nUsed))
				break;

			nReceiveSize -= nUsed;
			nTotalUsed += nUsed;

			if (true == m_Resolver.IsCompleted())
			{
				AutoLock(m_Lock);
				m_vecReceivedPacket.push_back(m_Resolver.GetReceivedPacket());
			}
		}
	}
}

void Bass::UDPServerImpl::_Destroy()
{
	AutoLock(m_Lock);
	Stop();
	SafeDelete(m_pThread);
}
