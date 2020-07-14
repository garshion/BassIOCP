#pragma once
#include "NetworkCommon.h"
#include "Packet.h"

#include <vector>
#include <mutex>

namespace Bass
{
	class PacketResolver
	{
	public:
		PacketResolver();
		~PacketResolver();
		void SetSocketIndex(const SocketIndex_t& socketIndex);

		bool Resolve(char* pBuffer, int nLength, int& nUsedBytes);
		Packet& GetReceivedPacket();
		bool IsCompleted() const;
	private:
		void _ClearBuffer();

	private:
		std::mutex m_Lock;

		char* m_pBuffer = nullptr;

		int m_nRemainHeaderSize = 0;
		int m_nPacketSize = 0;
		int m_nCurrentOffset;

		bool m_IsCompleted = false;

		Packet m_PacketData;
	};

}