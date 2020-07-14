#pragma once
#include <vector>
namespace Bass
{
	struct Packet;
	class UDPServerImpl;
	class UDPServer
	{
	public:
		UDPServer();
		~UDPServer();

		bool SetListenPort(int nPort);
		void Start();
		void Stop();
		void GetReceivedPacket(std::vector<Packet>& o_vecPacket);
	private:
		UDPServerImpl* m_pServer = nullptr;
	};

}