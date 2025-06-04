#pragma once
#include "NetworkCommon.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <atomic>

#include "MTQueue.h"
#include "Packet.h"
#include <chrono>


typedef std::vector<Bass::Packet> PacketList_t;

namespace Bass
{
	class CIOCPSocket;
	class CIOCPImpl
	{
	public:
		CIOCPImpl();
		~CIOCPImpl();

		void SetMinimalMode(bool onoff);
		bool Create(int nPort, const std::string& strLocalIP = "0.0.0.0", const size_t nMaxSessionCount = DEFAULT_SESSION_COUNT);
		
		// ��Ŷ ����
		void GetPacketList(PacketList_t& o_PacketList);

		// ��Ŷ ����
		bool SendPacket(Packet& data);		// 1Ŭ�� ����
		bool SendPacketToClients(Packet& data, std::vector<SocketIndex_t>& clients);	// �ټ�Ŭ�� ����
		bool SendPacketToAll(Packet& data);	// ��ü ����

		// for Session
		void DisconnectSession(SocketIndex_t nIndex);
		void FreeSocketIndex(SocketIndex_t nIndex);
		bool GetSessionIP(SocketIndex_t nindex, std::string& o_strIP);
		bool GetSessionPort(SocketIndex_t nIndex, int& o_nPort);

	private:
		void _CreateSession();

		CIOCPSocket* _GetFreeIOCPSocket();
		CIOCPSocket* _GetIOCPSocket(SocketIndex_t socketIndex);


		void _Release();
		bool _Bind();
		void _SocketNotify(SocketIndex_t socketIndex, ESocketNotify notify);

		// for Thread
		void _Worker();
		void _Writer();
		void _Listener();


	private:
		HANDLE m_hCompletionPort = NULL;
		SOCKET m_hListener = INVALID_SOCKET;
		DWORD m_dwTLSIndex = TLS_OUT_OF_INDEXES;

		std::string m_strLocalIPAddress = "0.0.0.0";
		int m_nListenPort = 0;

		std::vector<CIOCPSocket*> m_vecSessionList;
		std::unordered_map<int, CIOCPSocket*> m_mapSessionList;

		size_t m_nMaxSessionCount = DEFAULT_SESSION_COUNT;

		std::mutex m_PacketLock;
		PacketList_t m_vecPacketList;

		MTQueue<SocketIndex_t> m_queueSocketIndex;
		std::unordered_set<SocketIndex_t> m_setConnected;


		int m_nWorkerCount = 0;
		int m_nWriterCount = 0;

		std::vector<std::thread*> m_vecWorkerThread;
		std::vector<std::thread*> m_vecWriterThread;
		std::thread* m_pListenerThread = nullptr;

		std::chrono::system_clock::time_point m_StartTime;					// ���� ���۽ð�

		std::atomic_bool m_IsMinimal = false;								// �ּһ������ ������ ���� (������ ��ſ� � ���)
		std::atomic_bool m_bCreateFlag = false;								
		
		// Thread Condition Flag
		std::atomic_bool m_bListenerWorking = false;					
		std::atomic_bool m_bWorkerWorking = false;
		std::atomic_bool m_bWriterWorking = false;						


		// ���
		std::atomic_int64_t m_nTotalRecvBytes = 0;
		std::atomic_int64_t m_nRecvBytes = 0;
		std::atomic_int64_t m_nTotalSendBytes = 0;
		std::atomic_int64_t m_nSendBytes = 0;



	};

}