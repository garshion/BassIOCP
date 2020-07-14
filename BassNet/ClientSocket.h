#pragma once
#include <vector>

namespace Bass
{
	struct Packet;
	class ClientSocketImpl;
	class ClientSocket
	{
	public:
		ClientSocket();
		~ClientSocket();

		bool Connect(const char* strIP, const int& nPort);
		void Disconnect();
		bool Reconnect();

		void GetReceivedPacketList(std::vector<Packet>& o_packetList);

		bool SendPacket(Packet& data);
		bool IsConnected();
	private:
		ClientSocketImpl* m_pSocket = nullptr;
	};
}
