#include "UDPServer.h"
#include "UDPServerImpl.hxx"

Bass::UDPServer::UDPServer()
{
	m_pServer = new UDPServerImpl();
}

Bass::UDPServer::~UDPServer()
{
	Stop();
	SafeDelete(m_pServer);
}

bool Bass::UDPServer::SetListenPort(int nPort)
{
	if(nullptr == m_pServer)
		return false;
	return m_pServer->SetListenPort(nPort);
}

void Bass::UDPServer::Start()
{
	if (nullptr != m_pServer)
		m_pServer->Start();
}

void Bass::UDPServer::Stop()
{
	if (nullptr != m_pServer)
		m_pServer->Stop();
}

void Bass::UDPServer::GetReceivedPacket(std::vector<Packet>& o_vecPacket)
{
	if (nullptr != m_pServer)
		m_pServer->GetReceivedPacket(o_vecPacket);
}
