#pragma once
#include "NetworkCommon.h"

namespace Bass
{
	class UDPSenderImpl
	{
	public:
		UDPSenderImpl(const char* strHost = "", int nPort = 0);
		~UDPSenderImpl();

		void Send(char* pBuffer, int nBufferSize);
		void Send(char* pBuffer, int nBufferSize, const std::string& strHost, int nPort);

	private:
		void _MakeAddr();

	private:
		SOCKET m_Socket = INVALID_SOCKET;
		sockaddr_in m_Addr;
		int m_nAddrSize = sizeof(sockaddr_in);
		
		std::string m_strLastSendHost = "";
		USHORT m_nLastPort = 0;


	};
}