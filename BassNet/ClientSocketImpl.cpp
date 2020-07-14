#include "ClientSocketImpl.hxx"
#include "NetworkCore.h"

Bass::ClientSocketImpl::ClientSocketImpl()
{
	NetworkCore::GetInstance().InitSocket();
}

Bass::ClientSocketImpl::~ClientSocketImpl()
{
	Disconnect();
}

bool Bass::ClientSocketImpl::Connect(const char * strIP, int nPort)
{
	if (true == m_IsConnected)
		return true;

	if (nullptr == strIP)
		return false;
	if (0x00 >= nPort
		|| 0xFFFF < nPort)
		return false;

	m_strHost = strIP;
	m_nPort = nPort;

	return _Connect();
}

void Bass::ClientSocketImpl::Disconnect()
{
	m_bRunning = false;

	if (INVALID_SOCKET != m_hSocket)
	{
		shutdown(m_hSocket, SD_SEND);
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}

	m_IsConnected = false;
	SafeDelete(m_pThread);
}

bool Bass::ClientSocketImpl::Reconnect()
{
	Disconnect();
	return _Connect();
}

void Bass::ClientSocketImpl::GetReceivedPacketList(std::vector<Packet>& o_packetList)
{
	o_packetList.swap(m_vecPackets);
}

bool Bass::ClientSocketImpl::SendPacket(Packet & data)
{
	if (false == m_IsConnected
		|| INVALID_SOCKET == m_hSocket)
		return false;

	int nSendBytes = send(m_hSocket, data.pData, data.GetSize(), 0);
	if (nSendBytes <= 0)
		return false;

	return true;
}

bool Bass::ClientSocketImpl::IsConnected()
{
	return m_IsConnected;
}

bool Bass::ClientSocketImpl::_Connect()
{
	m_hSocket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_hSocket)
		return false;

	sockaddr_in addr;
	memset(&addr, 0x00, sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = (USHORT)htons((USHORT)m_nPort);
	InetPtonA(AF_INET, m_strHost.c_str(), &addr.sin_addr.S_un.S_addr);

	if (SOCKET_ERROR == connect(m_hSocket, (sockaddr*)&addr, sizeof(addr)))
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
		return false;
	}

	m_IsConnected = true;

	m_pThread = new std::thread(&Bass::ClientSocketImpl::_Worker, this);
	m_pThread->detach();

	return true;
}

bool Bass::ClientSocketImpl::_Worker()
{
	m_bRunning.store(true);

	char pBuffer[MAX_BUFFER_SIZE] = { 0, };

	while (true == m_bRunning)
	{
		int nRecvSize = recv(m_hSocket, pBuffer, MAX_BUFFER_SIZE, 0);
		if (nRecvSize > 0)
		{
			int nTotalUsed = 0;
			while (nRecvSize > 0)
			{
				int nUsedBytes = 0;

				if (false == m_Resolver.Resolve(pBuffer, nRecvSize, nUsedBytes))
					break;

				nRecvSize -= nUsedBytes;
				nTotalUsed += nUsedBytes;

				if (true == m_Resolver.IsCompleted())
				{
					m_vecPackets.push_back(m_Resolver.GetReceivedPacket());
				}
			}
		}
		else
		{
			if (true == NetworkCore::GetInstance().IsError(0))
				Disconnect();
		}

	}

	return true;
}

