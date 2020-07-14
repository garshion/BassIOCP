#pragma once
#include "NetworkCommon.h"
#include <vector>
#include <atomic>
#include "Overlapped.hxx"

#include "PacketResolver.hxx"

namespace Bass
{
	class CIOCPImpl;
	class CIOCPSocket
	{
	public:
		CIOCPSocket(SocketIndex_t nIndex);
		~CIOCPSocket();

		void SetSocket(SOCKET so);
		void Close(ENetworkResult ret);

		SocketIndex_t GetSocketIndex() const;
		void SetAddress(const char* strAddress, int nPort);

		void OnConnect();
		void OnRecvCompleted();
		void OnSendCompleted(COverlapped* pOver);
		bool Resolve(char* pBuffer, int nLength, int& nUsedBytes, bool& bCompleted);
		Packet& GetReceivedPacket();

		int Read();
		int Write();

		bool IsUsing();

		bool SendDataAdd(Packet& data);
		void SetIOCP(CIOCPImpl* pIOCP);

		const std::chrono::system_clock::time_point& GetLastReceiveTime() const;

		void GetPeerHost(std::string& o_strHost);
		void GetPeerPort(int& o_nPort);


	private:
		SocketIndex_t m_nSocketIndex = 0;
		std::string m_strPeerIP = "";
		int m_nPeerPort = 0;

		SOCKET m_hSocket = INVALID_SOCKET;
		bool m_bUsing = false;

		std::chrono::system_clock::time_point m_LastPacketRceiveTime;
		std::atomic_bool m_bOperationReadFlag = false;
		std::atomic_uint m_nOverlappedSendingCount = 0;

		std::mutex m_SendLock;
		std::vector<COverlapped*> m_vecWriteBuffer;
		COverlapped m_RecvBuffer;

		CIOCPImpl* m_pIOCP = nullptr;

		PacketResolver m_Resolver;



	};

}