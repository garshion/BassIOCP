#include "SampleServer.h"
#include <vector>
#include <Packet.h>
#include <LogManager.h>
#include <SampleCommon.h>
#include <thread>
#include "UserManager.h"
#include <StringUtil.h>


SampleServer::SampleServer()
{
}

SampleServer::~SampleServer()
{
}

void SampleServer::Start()
{
	if (true == m_ServerSocket.Create(SAMPLE_SERVER_PORT))
	{
		Bass::LogManager::Instance.System(L"Server Socket Created Success. Listen Port [%d]", SAMPLE_SERVER_PORT);
		std::thread thread(&SampleServer::_Run, this);
		thread.detach();
	}
	else
	{
		Bass::LogManager::Instance.Error(L"Server Socket Created Failed!!");
	}
}

bool SampleServer::_PacketProcess(int nIndex, Bass::Packet& packet)
{
	if (packet.eNotify != Bass::ESocketNotify::SOCKET_NOTIFY_PACKET)
		return false;

	using namespace Sample;
	switch ((EProtocol)packet.GetProtocol())
	{
	case EProtocol::CS_PING:
	{
		auto msg = packet.GetData<CSPing>();
		SCPong pong;
		pong.SourceTick = msg->SourceTick;
		Bass::Packet ret((int)EProtocol::SC_PONG, &pong);
		m_ServerSocket.SendPacket(nIndex, ret);
	}
	break;
	case EProtocol::CS_CONNECT_REQ:
	{
		auto msg = packet.GetData<CSConnectReq>();
		if (true == UserManager::Instance.AddUser(packet.nSenderIndex, std::string(msg->NickName)))
		{
			Bass::LogManager::Instance.Info(L"Socket (%d) User (%S) Add Success!", packet.nSenderIndex, msg->NickName);
		}

		SCConnectRes res;
		res.ConnectIndex = packet.nSenderIndex;
		Bass::Packet ret((int)EProtocol::SC_CONNECT_RES, &res);
		m_ServerSocket.SendPacket(nIndex, ret);
	}
	break;
	case EProtocol::CS_CHAT_REQ:
	{
		auto msg = packet.GetData<CSChatReq>();
		SCChatRes res;
		res.SetNickName(UserManager::Instance.GetUserNickName(nIndex));
		res.SetChatMessage(msg->ChatMessage);

		Bass::LogManager::Instance.Debug(L"%S : %S", res.NickName, res.ChatMessage);

		Bass::Packet ret((int)EProtocol::SC_CHAT_RES, &res);
		m_ServerSocket.SendPacketToClients(ret, UserManager::Instance.GetConnectedList());
	}
	break;

	default:
		Bass::LogManager::Instance.Warning(L"Inbalid Protocol Type!! Socket(%d) Protocol(%d)", nIndex, packet.GetProtocol());
		return false;
	}

	return true;
}

void SampleServer::_OnConnect(int nIndex)
{
	std::string strIP = "";
	m_ServerSocket.GetSessionIP(nIndex, strIP);
	Bass::LogManager::Instance.Info(L"Socket(%d) Connected! [%S]", nIndex, strIP.c_str());
}

void SampleServer::_OnDisconnect(int nIndex)
{
	std::string strNick = UserManager::Instance.GetUserNickName(nIndex);
	Bass::LogManager::Instance.Info(L"Socket(%d) User(%S) Disconnected.", nIndex, strNick.c_str());
	UserManager::Instance.RemoveUser(nIndex);
}

void SampleServer::_Run()
{
	m_bRunning = true;
	std::vector<Bass::Packet> vecPacketList;

	const double DELAY_SEC = 1.0 / 60.0;	// 60 fps

	auto nextWaitTime = std::chrono::system_clock::now() + std::chrono::duration<double>(0);

	Bass::LogManager::Instance.System(L"Server Main Loop Start");

	while (m_bRunning)
	{
		nextWaitTime = std::chrono::system_clock::now() + std::chrono::duration<double>(DELAY_SEC);
		vecPacketList.clear();
		m_ServerSocket.GetPacketList(vecPacketList);

		for (auto& packet : vecPacketList)
		{
			switch (packet.eNotify)
			{
			case Bass::ESocketNotify::SOCKET_NOTIFY_CONNECT:
				_OnConnect(packet.nSenderIndex);
				break;
			case Bass::ESocketNotify::SOCKET_NOTIFY_CLOSED:
				_OnDisconnect(packet.nSenderIndex);
				break;
			case Bass::ESocketNotify::SOCKET_NOTIFY_PACKET:
				_PacketProcess(packet.nSenderIndex, packet);
				break;
			default:
				Bass::LogManager::Instance.Error(L"Invalid Notify Type!! (%d)", (int)packet.eNotify);
				m_bRunning = false;
				break;
			}
		}

		std::this_thread::sleep_until(nextWaitTime);
	}

	Bass::LogManager::Instance.System(L"Server Main Loop End");

}
