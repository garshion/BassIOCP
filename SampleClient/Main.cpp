
#include <string>
#include <iostream>
#include <thread>

#include <ClientSocket.h>
#include <SampleCommon.h>
#include <Packet.h>

using namespace Sample;

Bass::ClientSocket so;

void Run()
{

	std::vector<Bass::Packet> vecList;

	while (so.IsConnected())
	{
		vecList.clear();
		so.GetReceivedPacketList(vecList);
		for (auto it : vecList)
		{
			switch ((EProtocol)it.GetProtocol())
			{
			case EProtocol::SC_CHAT_RES:
			{
				SCChatRes* res = it.GetData<SCChatRes>();
				std::cout << std::string(res->NickName) << " : " << std::string(res->ChatMessage) << std::endl;
			}
				break;
			default:
				break;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}


int main(void)
{
	//std::string st
	
	if (false == so.Connect("127.0.0.1", SAMPLE_SERVER_PORT))
	{
		std::cout << "Server Connect Failed" << std::endl;
		return 1;
	}

	std::this_thread::sleep_for(std::chrono::duration<double>(0.2));	// 0.2√  ¥Î±‚
	
	std::string strNick;

	while (strNick.empty())
	{
		std::cout << "Your Nickname ? : ";
		std::cin >> strNick;
	}


	if (true == so.IsConnected())
	{
		std::cout << "Server Connected !!" << std::endl;
		CSConnectReq req;
		req.SetNickName(strNick);
		Bass::Packet packet((int)EProtocol::CS_CONNECT_REQ, &req);
		so.SendPacket(packet);
	}


	std::thread th(&Run);
	th.detach();


	std::string strBuffer;

	while (so.IsConnected())
	{
		strBuffer.clear();
		//std::cout << "Chat >> ";
		std::cin >> strBuffer;

		if (false == strBuffer.empty())
		{
			CSChatReq req;
			req.SetChatMessage(strBuffer);
			Bass::Packet packet((int)EProtocol::CS_CHAT_REQ, &req);
			so.SendPacket(packet);
		}
	}

	std::cout << "Server Disconnected" << std::endl;


	return 0;
}