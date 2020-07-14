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
		
		// ��Ŷ ����
		void GetPacketList(std::vector<Bass::Packet>& o_PacketList);

		// ��Ŷ ����
		bool SendPacket(Packet& data);													// 1Ŭ�� ����
		bool SendPacketToClients(Packet& data, std::vector<SocketIndex_t>& clients);	// �ټ�Ŭ�� ����
		bool SendPacketToAll(Packet& data);												// ��ü ����

		// Session
		void DisconnectSession(SocketIndex_t nIndex);
		bool GetSessionIP(SocketIndex_t nindex, std::string& o_strIP);
		bool GetSessionPort(SocketIndex_t nIndex, int& o_nPort);


	private:
		CIOCPImpl* m_pIOCP = nullptr;
	};
}
