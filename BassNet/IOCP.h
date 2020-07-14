#pragma once
#include "NetworkCommon.h"
#include <vector>

namespace Bass
{
	struct Packet;
	class CIOCPImpl;
	class CIOCP
	{
	public:
		CIOCP();
		~CIOCP();

		bool Create(const int& nPort, const std::string& strBindIP = "0.0.0.0", const size_t nMaxSessionCount = DEFAULT_SESSION_COUNT);
		
		// 패킷 수신
		void GetPacketList(std::vector<Bass::Packet>& o_PacketList);

		// 패킷 전송
		bool SendPacket(Packet& data);													// 1클라 전송
		bool SendPacketToClients(Packet& data, std::vector<SocketIndex_t>& clients);	// 다수클라 전송
		bool SendPacketToAll(Packet& data);												// 전체 전송

		// Session
		void DisconnectSession(SocketIndex_t nIndex);
		bool GetSessionIP(SocketIndex_t nindex, std::string& o_strIP);
		bool GetSessionPort(SocketIndex_t nIndex, int& o_nPort);


	private:
		CIOCPImpl* m_pIOCP = nullptr;
	};
}
