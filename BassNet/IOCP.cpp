#include "IOCP.h"
#include "IOCPImpl.hxx"

Bass::CIOCP::CIOCP()
{
	m_pIOCP = new CIOCPImpl();
}

Bass::CIOCP::~CIOCP()
{
	SafeDelete(m_pIOCP);
}

bool Bass::CIOCP::Create(const int& nPort, const std::string& strBindIP, const size_t nMaxSessionCount)
{
	if (nullptr == m_pIOCP)
		return false;
	return m_pIOCP->Create(nPort, strBindIP, nMaxSessionCount);
}

void Bass::CIOCP::GetPacketList(std::vector<Bass::Packet>& o_PacketList)
{
	if (nullptr != m_pIOCP)
		m_pIOCP->GetPacketList(o_PacketList);
}

bool Bass::CIOCP::SendPacket(Packet& data)
{
	if (nullptr == m_pIOCP)
		return false;
	return m_pIOCP->SendPacket(data);
}

bool Bass::CIOCP::SendPacketToClients(Packet& data, std::vector<SocketIndex_t>& clients)
{
	if (nullptr == m_pIOCP)
		return false;

	return m_pIOCP->SendPacketToClients(data, clients);
}

bool Bass::CIOCP::SendPacketToAll(Packet& data)
{
	if (nullptr == m_pIOCP)
		return false;
	return m_pIOCP->SendPacketToAll(data);;
}

void Bass::CIOCP::DisconnectSession(SocketIndex_t nIndex)
{
	if (nullptr != m_pIOCP)
		m_pIOCP->DisconnectSession(nIndex);

}

bool Bass::CIOCP::GetSessionIP(SocketIndex_t nindex, std::string& o_strIP)
{
	if (nullptr == m_pIOCP)
		return false;
	return m_pIOCP->GetSessionIP(nindex, o_strIP);
}

bool Bass::CIOCP::GetSessionPort(SocketIndex_t nIndex, int& o_nPort)
{
	if (nullptr == m_pIOCP)
		return false;
	return m_pIOCP->GetSessionPort(nIndex, o_nPort);
}
