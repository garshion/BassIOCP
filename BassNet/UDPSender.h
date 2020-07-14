#pragma once
#include <vector>
#include <string>

namespace Bass
{
	struct Packet;
	class UDPSenderImpl;
	class UDPSender
	{
		UDPSender(const char* strHost = "", int nPort = 0);
		~UDPSender();

		void Send(char* pBuffer, int nBufferSize);
		void Send(char* pBuffer, int nBufferSize, const std::string& strHost, int nPort);

	private:
		UDPSenderImpl* m_pSender = nullptr;
	};

}
