#include "IOCPImpl.hxx"
#include "IOCPSocket.hxx"
#include "Overlapped.hxx"

void Bass::CIOCPImpl::_CreateSession()
{
	if (false == m_vecSessionList.empty())
		return;

	if (m_nMaxSessionCount == 0)
		return;

	for (SocketIndex_t i = 0; i < (SocketIndex_t)m_nMaxSessionCount; ++i)
	{
		auto pSession = new CIOCPSocket(i);
		pSession->SetIOCP(this);
		m_vecSessionList.push_back(pSession);
		m_queueSocketIndex.Push(i);
	}
}

Bass::CIOCPSocket * Bass::CIOCPImpl::_GetFreeIOCPSocket()
{
	SocketIndex_t socketIndex = 0;

	if (false == m_queueSocketIndex.Pop(socketIndex))
		return nullptr;

	CIOCPSocket* pSocket = _GetIOCPSocket(socketIndex);
	if (nullptr == pSocket
		|| pSocket->IsUsing())
		return nullptr;

	return pSocket;
}

Bass::CIOCPSocket * Bass::CIOCPImpl::_GetIOCPSocket(SocketIndex_t socketIndex)
{
	if (m_vecSessionList.size() <= socketIndex)
		return nullptr;
	return m_vecSessionList.at(socketIndex);
}

void Bass::CIOCPImpl::_Release()
{
	m_bListenerWorking = false;
	m_bWriterWorking = false;
	m_bWorkerWorking = false;
	m_bCreateFlag = false;
	m_IsMinimal = false;

	if (NULL != m_hCompletionPort)
	{

		if (INVALID_SOCKET != m_hListener)
		{
			closesocket(m_hListener);
			m_hListener = INVALID_SOCKET;
		}

		SafeDelete(m_pListenerThread);

		for (size_t i = 0; i < m_vecWorkerThread.size(); ++i)
			PostQueuedCompletionStatus(m_hCompletionPort, 0, NULL, NULL);

		for (auto pThread : m_vecWorkerThread)
			SafeDelete(pThread);
		m_vecWorkerThread.clear();



		for (auto pThread : m_vecWriterThread)
			SafeDelete(pThread);
		m_vecWriterThread.clear();

		for (auto pSocket : m_vecSessionList)
		{
			if (nullptr != pSocket
				&& true == pSocket->IsUsing())
				pSocket->Close(ENetworkResult::NETWORK_RESULT_SERVER_RELEASE);
			SafeDelete(pSocket);
		}
		m_vecSessionList.clear();

		m_vecPacketList.clear();

		m_nWorkerCount = 0;
		m_nWriterCount = 0;

		SocketIndex_t idx = 0;
		while (true == m_queueSocketIndex.Pop(idx))
		{
		}

		m_nMaxSessionCount = DEFAULT_SESSION_COUNT;
		m_strLocalIPAddress = "0.0.0.0";

		if (m_dwTLSIndex != TLS_OUT_OF_INDEXES)
		{
			TlsFree(m_dwTLSIndex);
			m_dwTLSIndex = TLS_OUT_OF_INDEXES;
		}

		CloseHandle(m_hCompletionPort);
		m_hCompletionPort = NULL;

	}
}

bool Bass::CIOCPImpl::_Bind()
{
	if (INVALID_SOCKET != m_hListener)
		return false;

	m_hListener = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if (INVALID_SOCKET == m_hListener)
		return false;

	SOCKADDR_IN sa;
	memset(&sa, 0x00, sizeof(SOCKADDR_IN));
	sa.sin_family = AF_INET;
	sa.sin_port = htons((u_short)m_nListenPort);

	if (SOCKET_ERROR == ::bind(m_hListener, (LPSOCKADDR)&sa, sizeof(SOCKADDR_IN)))
	{
		closesocket(m_hListener);
		m_hListener = INVALID_SOCKET;
		return false;
	}

	return true;
}

void Bass::CIOCPImpl::_Worker()
{
	m_bWorkerWorking = true;

	COverlapped* pOver = nullptr;
	DWORD dwRead = 0;
	CIOCPSocket* pSocket = nullptr;
	BOOL bRet = FALSE;

	do
	{
		pOver = nullptr;
		dwRead = 0;
		pSocket = nullptr;
		bRet = GetQueuedCompletionStatus(m_hCompletionPort, &dwRead, (PULONG_PTR)&pSocket, (LPOVERLAPPED*)&pOver, INFINITE);

		if (FALSE == bRet)
		{
			int nError = GetNetworkError();
			ENetworkResult eRet = ENetworkResult::NETWORK_RESULT_OK;

			if (ERROR_SUCCESS == nError
				&& 0 == dwRead)
				eRet = ENetworkResult::NETWORK_RESULT_SOCKET_CLOSED;		// Socket Closed
			else if (nullptr == pOver)
				eRet = ENetworkResult::NETWORK_RESULT_NO_OVERLAPPED_DATA;	// IO 작업이 완료된 패킷이 나오지 않음.
			else
				eRet = ENetworkResult::NETWORK_RESULT_NO_OVERLAPPED_DATA;	// IOCP 작업 자체를 실패한 경우. 자세한 내용은 nError 참고.

			SafeDeleteOverlapped(pOver);
			if (nullptr != pSocket)
			{
				_SocketNotify(pSocket->GetSocketIndex(), ESocketNotify::SOCKET_NOTIFY_CLOSED);
				pSocket->Close(eRet);
			}

			continue;
		}

		if (nullptr == pSocket
			|| nullptr == pOver)
		{
			if (true == m_IsMinimal)
				m_bWorkerWorking = false;
			break;	// 이 소켓은 죽었슴돠.
		}

		if (0 == dwRead)
		{
			SafeDeleteOverlapped(pOver);
			_SocketNotify(pSocket->GetSocketIndex(), ESocketNotify::SOCKET_NOTIFY_CLOSED);
			pSocket->Close(ENetworkResult::NETWORK_RESULT_NO_DATA_READ);
			continue;
		}

		switch (pOver->Mode())
		{
		case EOperationMode::OPERATION_MODE_READ:
		{
			m_nTotalRecvBytes += dwRead;
			m_nRecvBytes += dwRead;

			int nBytesRecved = dwRead;
			int nTotalUsed = 0;

			while (nBytesRecved > 0)
			{
				int nBytesUsed = 0;
				bool bCompleted = false;
				if (false == pSocket->Resolve(pOver->GetBuffer().buf + nTotalUsed, nBytesRecved, nBytesUsed, bCompleted))
				{
					//pSocket->ResetBuffer();
					break;
				}
				nBytesRecved -= nBytesUsed;
				nTotalUsed += nBytesUsed;

				if (true == bCompleted)
				{
					AutoLock(m_PacketLock);
					m_vecPacketList.push_back(pSocket->GetReceivedPacket());
					//pSocket->ResetBuffer();
				}

			}

			pSocket->OnRecvCompleted();
		}
		break;
		case EOperationMode::OPERATION_MODE_WRITE:
		{
			if ((int)dwRead < pOver->GetBuffer().len)
			{
				SafeDeleteOverlapped(pOver);
				_SocketNotify(pSocket->GetSocketIndex(), ESocketNotify::SOCKET_NOTIFY_CLOSED);
				pSocket->Close(ENetworkResult::NETWORK_RESULT_CANNOT_SEND_ENOUGH);
			}
			else
			{
				pSocket->OnSendCompleted(pOver);
			}
		}
		break;
		default:
			break;
		}
	} while (true == m_bWorkerWorking);

}

void Bass::CIOCPImpl::_Writer()
{
	m_bWriterWorking = true;
	std::chrono::system_clock::time_point sleepTime = std::chrono::system_clock::now() + std::chrono::milliseconds(WRITE_THREAD_DELAY_MS);

	do
	{
		for (auto pSocket : m_vecSessionList)
		{
			if (nullptr != pSocket)
				pSocket->Write();
		}
		std::this_thread::sleep_until(sleepTime);
		sleepTime += std::chrono::milliseconds(WRITE_THREAD_DELAY_MS);
	} while (true == m_bWriterWorking);
}

void Bass::CIOCPImpl::_Listener()
{
	if (false == _Bind())
		return;

	if (SOCKET_ERROR == listen(m_hListener, SOMAXCONN))
		return;

	SOCKET so = INVALID_SOCKET;
	sockaddr_in addr;
	int nAddrSize = sizeof(sockaddr_in);
	std::string strPeerAddress = "";
	int nPeerPort = 0;
	CIOCPSocket* pSocket = nullptr;

	m_bListenerWorking = true;

	do
	{
		so = WSAAccept(m_hListener, (sockaddr*)&addr, &nAddrSize, NULL, 0);
		if (INVALID_SOCKET == so)
		{
			m_bListenerWorking = false;
			break;
		}

		char szAddrTemp[MAX_PATH] = { 0, };
		InetNtopA(AF_INET, &addr.sin_addr, szAddrTemp, sizeof(szAddrTemp));
		strPeerAddress = szAddrTemp;

		nPeerPort = ntohs(addr.sin_port);

		pSocket = _GetFreeIOCPSocket();
		if (nullptr == pSocket)
		{
			// 세션 가득참
			closesocket(so);
			continue;
		}

		pSocket->SetSocket(so);

		HANDLE hRet = CreateIoCompletionPort((HANDLE)so, m_hCompletionPort, (ULONG_PTR)pSocket, 0);
		if (NULL == hRet)
		{
			pSocket->Close(ENetworkResult::NETWORK_RESULT_CANNOT_CREATE_IOCP_PEER);
			continue;
		}
		pSocket->SetAddress(strPeerAddress.c_str(), nPeerPort);
		pSocket->OnConnect();
		_SocketNotify(pSocket->GetSocketIndex(), ESocketNotify::SOCKET_NOTIFY_CONNECT);
		pSocket->Read();

	} while (true == m_bListenerWorking);

}

void Bass::CIOCPImpl::_SocketNotify(SocketIndex_t socketIndex, ESocketNotify notify)
{
	Packet packet;
	packet.nSenderIndex = socketIndex;
	packet.eNotify = notify;

	if (notify == ESocketNotify::SOCKET_NOTIFY_CONNECT
		&& m_setConnected.end() == m_setConnected.find(socketIndex))
		m_setConnected.insert(socketIndex);
	else if (notify == ESocketNotify::SOCKET_NOTIFY_CLOSED)
	{
		auto it = m_setConnected.find(socketIndex);
		if (m_setConnected.end() != it)
			m_setConnected.erase(it);
	}

	AutoLock(m_PacketLock);
	m_vecPacketList.push_back(packet);
}

Bass::CIOCPImpl::CIOCPImpl()
{
}

Bass::CIOCPImpl::~CIOCPImpl()
{
	_Release();
}

void Bass::CIOCPImpl::SetMinimalMode(bool onoff)
{
	m_IsMinimal = onoff;
}

bool Bass::CIOCPImpl::Create(int nPort, const std::string & strLocalIP, const size_t nMaxSessionCount)
{
	if (true == m_bCreateFlag)
		return false;

	if (0x00 >= nPort
		|| 0xFFFF < nPort)
		return false;

	m_nMaxSessionCount = 0 == nMaxSessionCount ? DEFAULT_SESSION_COUNT : nMaxSessionCount;
	m_nListenPort = nPort;
	m_strLocalIPAddress = strLocalIP.empty() ? "0.0.0.0" : strLocalIP;

	_CreateSession();

	//m_nWorkerCount = m_IsMinimal ? 1 : SystemInfoManager::GetInstance().GetProcessorCount();
	m_nWorkerCount = m_IsMinimal ? 1 : 4;	// 임시 처리.
	m_nWriterCount = m_IsMinimal ? 1 : SIZE_IOCP_WRITER_THREAD;

	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, (DWORD)m_nWorkerCount);
	if (NULL == m_hCompletionPort)
	{
		_Release();
		return false;
	}

	m_dwTLSIndex = TlsAlloc();
	if (m_dwTLSIndex == TLS_OUT_OF_INDEXES)
	{
		_Release();
		return false;
	}

	m_pListenerThread = new std::thread(&Bass::CIOCPImpl::_Listener, this);
	m_pListenerThread->detach();

	for (int i = 0; i < m_nWorkerCount; ++i)
	{
		std::thread* pThread = new std::thread(&Bass::CIOCPImpl::_Worker, this);
		pThread->detach();
		m_vecWorkerThread.push_back(pThread);
	}

	for (int i = 0; i < m_nWriterCount; ++i)
	{
		std::thread* pThread = new std::thread(&Bass::CIOCPImpl::_Writer, this);
		pThread->detach();
		m_vecWriterThread.push_back(pThread);
	}

	m_bCreateFlag = true;

	m_StartTime = std::chrono::system_clock::now();
	return true;
}

void Bass::CIOCPImpl::GetPacketList(PacketList_t & o_PacketList)
{
	o_PacketList.clear();
	AutoLock(m_PacketLock);
	o_PacketList.swap(m_vecPacketList);
}

bool Bass::CIOCPImpl::SendPacket(Packet & data)
{
	int nSize = data.GetSize();

	if (PACKET_HEADER_SIZE > nSize)
		return false;

	CIOCPSocket* pSocket = _GetIOCPSocket(data.nSenderIndex);
	if (nullptr == pSocket
		|| false == pSocket->IsUsing())
		return false;

	if (false == pSocket->SendDataAdd(data))
		return false;

	m_nTotalSendBytes += nSize;
	m_nSendBytes += nSize;

	return true;
}

bool Bass::CIOCPImpl::SendPacketToClients(Packet & data, std::vector<SocketIndex_t>& clients)
{
	if (true == clients.empty())
		return false;

	int nSize = data.GetSize();

	if (PACKET_HEADER_SIZE > nSize)
		return false;

	for (SocketIndex_t idx : clients)
	{
		data.nSenderIndex = idx;
		SendPacket(data);
	}

	return true;
}

bool Bass::CIOCPImpl::SendPacketToAll(Packet & data)
{
	if (PACKET_HEADER_SIZE > data.GetSize())
		return false;

	for (auto idx : m_setConnected)
	{
		data.nSenderIndex = idx;
		SendPacket(data);
	}

	return true;
}

void Bass::CIOCPImpl::DisconnectSession(SocketIndex_t nIndex)
{
	auto pSession = _GetIOCPSocket(nIndex);
	if (nullptr == pSession)
		return;

	pSession->Close(ENetworkResult::NETWORK_RESULT_CLOSE_BY_APPLICATION);
}

void Bass::CIOCPImpl::FreeSocketIndex(SocketIndex_t nIndex)
{
	m_queueSocketIndex.Push(nIndex);
}

bool Bass::CIOCPImpl::GetSessionIP(SocketIndex_t nindex, std::string & o_strIP)
{
	o_strIP = "";

	auto pSession = _GetIOCPSocket(nindex);

	if (nullptr == pSession)
		return false;

	pSession->GetPeerHost(o_strIP);

	return true;
}

bool Bass::CIOCPImpl::GetSessionPort(SocketIndex_t nIndex, int & o_nPort)
{
	o_nPort = 0;

	auto pSession = _GetIOCPSocket(nIndex);

	if (nullptr == pSession)
		return false;

	pSession->GetPeerPort(o_nPort);

	return true;
}
