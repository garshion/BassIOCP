#pragma once
#include "NetworkCommon.h"

namespace Bass
{
	struct Packet
	{
		SocketIndex_t nSenderIndex = 0;
		char pData[MAX_PACKET_SIZE] = { 0, };
		ESocketNotify eNotify = ESocketNotify::SOCKET_NOTIFY_PACKET;

		////////////////////////////////////////////////////////////////////////////////
		// Constructor

		Packet() {}
		Packet(const ProtocolSize_t& protocol)
		{
			SetProtocol(protocol);
			SetSize(PACKET_HEADER_SIZE);
		}

		template<typename T>
		Packet(const ProtocolSize_t& protocol, const T* i_pData)
		{
			SetProtocol(protocol);
			if (nullptr == i_pData)
				SetSize(PACKET_HEADER_SIZE);
			else
				SetData(i_pData);
		}


		////////////////////////////////////////////////////////////////////////////////
		// Set

		void SetProtocol(const ProtocolSize_t& protocol)
		{
			memcpy_s(pData, PACKET_PROTOCOL_SIZE, &protocol, PACKET_PROTOCOL_SIZE);
		}

		void SetSize(const size_t& nSize)
		{
			LengthSize_t unSize = (LengthSize_t)nSize;
			memcpy_s(pData + PACKET_PROTOCOL_SIZE, PACKET_LENGTH_SIZE, &unSize, PACKET_LENGTH_SIZE);
		}

		bool SetData(const char* i_pData, size_t nSize)
		{
			if (nullptr == i_pData)
				return false;
			if (nSize > MAX_PACKET_SIZE - PACKET_HEADER_SIZE)
				return false;

			memcpy_s(pData + PACKET_HEADER_SIZE, MAX_PACKET_SIZE - PACKET_HEADER_SIZE, i_pData, nSize);
			SetSize(nSize + PACKET_HEADER_SIZE);
			return true;
		}

		template<typename T>
		bool SetData(const T* i_pData)
		{
			return SetData((const char*)i_pData, sizeof(T));
		}


		////////////////////////////////////////////////////////////////////////////////
		// Get

		const ProtocolSize_t& GetProtocol()
		{
			return *(ProtocolSize_t*)(pData);
		}

		const LengthSize_t& GetSize()
		{
			return *(LengthSize_t*)(pData + PACKET_PROTOCOL_SIZE);
		}

		const char* GetData()
		{
			return pData + PACKET_HEADER_SIZE;
		}

		template<typename T>
		T* GetData()
		{
			if (sizeof(T) > MAX_PACKET_SIZE - PACKET_HEADER_SIZE)
				return nullptr;
			return (T*)(pData + PACKET_HEADER_SIZE);
		}
	};

}