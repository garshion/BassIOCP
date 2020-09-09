#pragma once
#include <cstdint>
#include <string>

/*
* 테스트용 프로토콜 정의 파일.
* 
* 프로토콜 버퍼, 플랫버퍼 등 다른 IDL 류를 사용해도 무방하고, 다른 방식으로 구현해도 된다.
*/

#pragma pack(push, 1)
namespace Sample
{
	enum class EProtocol : int
	{
		None = 0,

		CS_CONNECT_REQ,			// 최초 접속 패킷. 닉네임 설정
		SC_CONNECT_RES,			// 


		CS_PING,				// 
		SC_PONG,				// 
		SC_PING,				// 
		CS_PONG,				// 


		CS_CHAT_REQ,			// 채팅 메시지 전송
		SC_CHAT_RES,			// 채팅 메시지 결과 (Broadcast)

	};

	struct CSPing
	{
		int64_t SourceTick = 0;
	};

	using SCPong = CSPing;
	using SCPing = CSPing;
	using CSPong = CSPing;

	constexpr size_t MAX_NICKNAME_SIZE = 20;

	struct CSConnectReq
	{
		char NickName[MAX_NICKNAME_SIZE + 1] = { 0, };

		bool SetNickName(const std::string& strNick)
		{
			if (true == strNick.empty()
				|| MAX_NICKNAME_SIZE < strNick.size())
				return false;

			memcpy_s(NickName, MAX_NICKNAME_SIZE, strNick.c_str(), strNick.size());
			return true;
		}
	};

	struct SCConnectRes
	{
		int ConnectIndex = 0;
	};

	constexpr size_t MAX_CHAT_SIZE = 100;

	struct CSChatReq
	{
		char ChatMessage[MAX_CHAT_SIZE + 1] = { 0, };
		bool SetChatMessage(const std::string& strChat)
		{
			if (true == strChat.empty()
				|| MAX_CHAT_SIZE < strChat.size())
				return false;

			memcpy_s(ChatMessage, MAX_CHAT_SIZE, strChat.c_str(), strChat.size());
			return true;
		}
	};

	struct SCChatRes
	{
		char NickName[MAX_NICKNAME_SIZE + 1] = { 0, };
		char ChatMessage[MAX_CHAT_SIZE + 1] = { 0, };

		bool SetNickName(const std::string& strNick)
		{
			if (true == strNick.empty()
				|| MAX_NICKNAME_SIZE < strNick.size())
				return false;

			memcpy_s(NickName, MAX_NICKNAME_SIZE, strNick.c_str(), strNick.size());
			return true;
		}

		bool SetChatMessage(const std::string& strChat)
		{
			if (true == strChat.empty()
				|| MAX_CHAT_SIZE < strChat.size())
				return false;

			memcpy_s(ChatMessage, MAX_CHAT_SIZE, strChat.c_str(), strChat.size());
			return true;
		}

	};


}

#pragma pack(pop)