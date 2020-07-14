#pragma once
#include "NetworkCommon.h"
#include "Packet.h"
#include <vector>
#include <atomic>
#include "PacketResolver.hxx"
namespace Bass
{

	class UDPServerImpl
	{
	public:
		UDPServerImpl();
		~UDPServerImpl();

		bool SetListenPort(int nPort);
		void Start();
		void Stop();

		void GetReceivedPacket(std::vector<Packet>& o_vecPacket);

		
	private:
		void _Process();

		void _Destroy();
		int _Receive(char* pBuffer, int nBufferSize);
	private:
		SOCKET m_Socket = INVALID_SOCKET;
		std::thread* m_pThread = nullptr;
		std::mutex m_Lock;
		std::atomic_bool m_isRunning = false;

		
		PacketResolver m_Resolver; 
		std::vector<Packet> m_vecReceivedPacket;

		sockaddr_in m_addr;
		int m_nAddrSize = sizeof(sockaddr_in);
		
	};

}