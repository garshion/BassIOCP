#include "IOCPSocket.hxx"
#include "Overlapped.hxx"
#include "IOCPImpl.hxx"
#include "NetworkCore.h"

Bass::CIOCPSocket::CIOCPSocket(SocketIndex_t nIndex)
	: m_RecvBuffer(EOperationMode::OPERATION_MODE_READ, EOverlappedType::OVERLAPPED_TYPE_STATIC)
{
	m_nSocketIndex = nIndex;
	m_Resolver.SetSocketIndex(nIndex);
}

Bass::CIOCPSocket::~CIOCPSocket()
{
	if (true == m_bUsing)
		Close(ENetworkResult::NETWORK_RESULT_IOCPSOCKET_DESTROYED);

	AutoLock(m_SendLock);
	for (auto pData : m_vecWriteBuffer)
		SafeDeleteOverlapped(pData);
	m_vecWriteBuffer.clear();
}

void Bass::CIOCPSocket::SetSocket(SOCKET so)
{
	if (true == m_bUsing)
		return;

	m_hSocket = so;
	BOOL bOption = TRUE;
	setsockopt(m_hSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&bOption, sizeof(BOOL));

	m_bUsing = true;
}

void Bass::CIOCPSocket::Close([[maybe_unused]] ENetworkResult ret)
{
	if (false == m_bUsing)
		return;

	m_bUsing = false;

	if (INVALID_SOCKET != m_hSocket)
	{
		shutdown(m_hSocket, SD_SEND);
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}

	AutoLock(m_SendLock);
	for (auto pData : m_vecWriteBuffer)
		SafeDelete(pData);
	m_vecWriteBuffer.clear();

	m_bOperationReadFlag = false;
	m_RecvBuffer.Reset();
	m_nPeerPort = 0;
	m_strPeerIP = "";

	if (nullptr != m_pIOCP)
		m_pIOCP->FreeSocketIndex(m_nSocketIndex);

}

SocketIndex_t Bass::CIOCPSocket::GetSocketIndex() const
{
	return m_nSocketIndex;
}

void Bass::CIOCPSocket::SetAddress(const char * strAddress, int nPort)
{
	m_strPeerIP = strAddress;
	m_nPeerPort = nPort;
}

void Bass::CIOCPSocket::OnConnect()
{
	m_nOverlappedSendingCount = 0;
}

void Bass::CIOCPSocket::OnRecvCompleted()
{
	m_LastPacketRceiveTime = std::chrono::system_clock::now();
	m_bOperationReadFlag = false;
	Read();
}

void Bass::CIOCPSocket::OnSendCompleted(COverlapped * pOver)
{
	if (m_nOverlappedSendingCount != 0)
		m_nOverlappedSendingCount--;
	SafeDeleteOverlapped(pOver);
	Write();
}


bool Bass::CIOCPSocket::Resolve(char * pBuffer, int nLength, int & nUsedBytes, bool & bCompleted)
{
	bCompleted = false;
	
	if (false == m_Resolver.Resolve(pBuffer, nLength, nUsedBytes))
		return false;
	
	bCompleted = m_Resolver.IsCompleted();
	return true;
}

Bass::Packet & Bass::CIOCPSocket::GetReceivedPacket()
{
	return m_Resolver.GetReceivedPacket();
}

int Bass::CIOCPSocket::Read()
{
	if (false == m_bUsing
		|| INVALID_SOCKET == m_hSocket
		|| true == m_bOperationReadFlag)
		return 0;

	m_bOperationReadFlag = true;
	m_RecvBuffer.Reset();

	DWORD dwRecvBytes = 0;
	DWORD dwFlag = 0;

	int nRet = WSARecv(m_hSocket, &m_RecvBuffer.GetBuffer(), 1, &dwRecvBytes, &dwFlag, &m_RecvBuffer, NULL);
	if (0 != nRet)
	{
		int nError = GetNetworkError();
		if (true == NetworkCore::GetInstance().IsError(nError))
		{
			m_bOperationReadFlag = false;
			Close(ENetworkResult::NETWORK_RESULT_RECV_ERROR);
			return 0;
		}
	}

	return (int)dwRecvBytes;
}

int Bass::CIOCPSocket::Write()
{
	if (false == m_bUsing
		|| true == m_vecWriteBuffer.empty())
		return 0;

	if (m_nOverlappedSendingCount > SIZE_MAX_OVERLAPPED_SENDING_COUNT)
		return 0;

	AutoLock(m_SendLock);

	auto pOver = m_vecWriteBuffer.at(0);
	m_vecWriteBuffer.erase(m_vecWriteBuffer.begin());

	m_nOverlappedSendingCount++;

	DWORD dwSendBytes = 0;
	int nRet = WSASend(m_hSocket, &pOver->GetBuffer(), 1, &dwSendBytes, 0, pOver, NULL);

	if (0 != nRet)
	{
		if (true == NetworkCore::GetInstance().IsError(0))
		{
			SafeDeleteOverlapped(pOver);
			m_nOverlappedSendingCount--;
			Close(ENetworkResult::NETWORK_RESULT_SEND_ERROR);
			return 0;
		}
	}

	return (int)dwSendBytes;
}

bool Bass::CIOCPSocket::IsUsing()
{
	return m_bUsing;
}

bool Bass::CIOCPSocket::SendDataAdd(Packet & data)
{
	if (false == m_bUsing)
		return false;

	SSendedOverlappedInfo over;
	over.Reset();
	COverlapped* pOver = nullptr;

	AutoLock(m_SendLock);
	if (false == m_vecWriteBuffer.empty())
		pOver = m_vecWriteBuffer.back();

	if (true == m_vecWriteBuffer.empty()
		|| nullptr == pOver
		|| false == pOver->AddData(&over, data.pData, data.GetSize()))
	{
		pOver = new COverlapped(EOperationMode::OPERATION_MODE_WRITE, EOverlappedType::OVERLAPPED_TYPE_DYNAMIC);
		if (false == pOver->AddData(&over, data.pData, data.GetSize()))
		{
			SafeDeleteOverlapped(pOver);
			return false;
		}
		m_vecWriteBuffer.push_back(pOver);
	}

	return true;
}

void Bass::CIOCPSocket::SetIOCP(CIOCPImpl* pIOCP)
{
	m_pIOCP = pIOCP;
}

const std::chrono::system_clock::time_point & Bass::CIOCPSocket::GetLastReceiveTime() const
{
	return m_LastPacketRceiveTime;
}

void Bass::CIOCPSocket::GetPeerHost(std::string & o_strHost)
{
	o_strHost = m_strPeerIP;
}

void Bass::CIOCPSocket::GetPeerPort(int & o_nPort)
{
	o_nPort = m_nPeerPort;
}
