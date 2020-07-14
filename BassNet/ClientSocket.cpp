#include "ClientSocket.h"
#include "ClientSocketImpl.hxx"

Bass::ClientSocket::ClientSocket()
{
	m_pSocket = new ClientSocketImpl();
}

Bass::ClientSocket::~ClientSocket()
{
	Disconnect();
	SafeDelete(m_pSocket);
}

bool Bass::ClientSocket::Connect(const char* strIP, const int& nPort)
{
	if (nullptr == m_pSocket)
		return false;
	return m_pSocket->Connect(strIP, nPort);
}

void Bass::ClientSocket::Disconnect()
{
	if (nullptr != m_pSocket)
		m_pSocket->Disconnect();
}

bool Bass::ClientSocket::Reconnect()
{
	if (nullptr == m_pSocket)
		return false;
	return m_pSocket->Reconnect();
}

void Bass::ClientSocket::GetReceivedPacketList(std::vector<Packet>& o_packetList)
{
	if (nullptr != m_pSocket)
		m_pSocket->GetReceivedPacketList(o_packetList);
}

bool Bass::ClientSocket::SendPacket(Packet& data)
{
	if (nullptr == m_pSocket)
		return false;
	return m_pSocket->SendPacket(data);
}

bool Bass::ClientSocket::IsConnected()
{
	if (nullptr == m_pSocket)
		return false;
	return m_pSocket->IsConnected();
}
