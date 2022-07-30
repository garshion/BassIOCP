#pragma once
#include "NetworkCommon.h"

#define SafeDeleteOverlapped(x) {											\
	if (nullptr != x) {														\
		if (x->Type() == Bass::EOverlappedType::OVERLAPPED_TYPE_DYNAMIC) 	\
		{ 																	\
			delete x; 														\
			x = nullptr; 													\
		}																	\
		else 																\
		{ 																	\
			x->Reset(); 													\
		}																	\
	}																		\
}																			

namespace Bass
{
	class COverlapped;

	enum class EOperationMode : unsigned char
	{
		OPERATION_MODE_READ = 0,
		OPERATION_MODE_WRITE,
	};

	enum class EOverlappedType : unsigned char
	{
		OVERLAPPED_TYPE_STATIC = 0,
		OVERLAPPED_TYPE_DYNAMIC,
	};


	struct SSendedOverlappedInfo
	{
		COverlapped *pOver = nullptr;
		char* pData = nullptr;
		int nSize = 0;
		void Reset()
		{
			pOver = nullptr;
			pData = nullptr;
			nSize = 0;
		}
	};


	class COverlapped : public OVERLAPPED
	{
	public:
		COverlapped(const EOperationMode& eMode, const EOverlappedType& eType);
		~COverlapped();

		const EOperationMode& Mode() const;
		const EOverlappedType& Type() const;
		WSABUF& GetBuffer();

		bool AddData(SSendedOverlappedInfo* pInfo, char* pData, const size_t& nSize);
		int GetDataSize();
		void Reset();

	private:
		EOperationMode m_Mode = EOperationMode::OPERATION_MODE_READ;
		EOverlappedType m_Type = EOverlappedType::OVERLAPPED_TYPE_STATIC;
		WSABUF m_WSABuf;
		char m_pBuffer[MAX_PACKET_SIZE] = { 0, };
	};

}

