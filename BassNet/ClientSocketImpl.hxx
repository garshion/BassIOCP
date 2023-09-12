#pragma once
#include "NetworkCommon.h"
#include "Packet.h"
#include "PacketResolver.hxx"
#include <vector>
#include <atomic>

namespace std
{
	class thread;
}

namespace Bass
{
	class ClientSocketImpl
	{
	public:
		ClientSocketImpl();
		~ClientSocketImpl();

		bool Connect(const char* strIP, int nPort);
		void Disconnect();
		bool Reconnect();

		void GetReceivedPacketList(std::vector<Packet>& o_packetList);

		bool SendPacket(Packet& data);
		bool IsConnected();

	private:
		bool _Connect();
		bool _Worker();
	private:
		SOCKET m_hSocket = INVALID_SOCKET;
		int m_nPort = 0;
		std::string m_strHost = "";
		bool m_IsConnected = false;

		std::thread* m_pThread = nullptr;
		std::atomic_bool m_bRunning = false;

		std::vector<Packet> m_vecPackets;
		PacketResolver m_Resolver;

		std::mutex m_PacketLock;
	};

}