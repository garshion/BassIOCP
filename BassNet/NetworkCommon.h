#pragma once

////////////////////////////////////////////////////////////////////////////////
// Windows Network Header

#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#endif

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

// end, Windows Network Header
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include "BassCommon.h"

using SocketIndex_t = int;	

#ifdef USE_SHORT_HEADER
using LengthSize_t = unsigned short;
using ProtocolSize_t = unsigned short;
#else
using LengthSize_t = int;
using ProtocolSize_t = int;
#endif



namespace Bass
{
	////////////////////////////////////////////////////////////////////////////////
	// Define Const Section


	// 패킷 규격
#if defined USE_JUMBO_PACKET
	constexpr size_t MAX_PACKET_SIZE = 8000;	// Using Jumbo Packet 
#else
	constexpr size_t MAX_PACKET_SIZE = 1440;	// MTU 1500 - TCP Header size 20 - Tcp Header Option Size 40
#endif

	constexpr size_t PACKET_PROTOCOL_SIZE = sizeof(ProtocolSize_t);
	constexpr size_t PACKET_LENGTH_SIZE = sizeof(LengthSize_t);
	constexpr size_t PACKET_HEADER_SIZE = PACKET_LENGTH_SIZE + PACKET_PROTOCOL_SIZE;

	// 네트워크 기본값
	constexpr size_t MAX_BUFFER_SIZE = MAX_PACKET_SIZE * 2;
	constexpr size_t DEFAULT_SESSION_COUNT = 5000;		



	// IOCP 설정
	constexpr size_t SIZE_IOCP_WRITER_THREAD = 1;
	constexpr size_t LISTENER_THREAD_COUNT = 1;
	constexpr size_t WRITE_THREAD_DELAY_MS = 30;

	constexpr size_t SIZE_MAX_OVERLAPPED_SENDING_COUNT = 3;



	////////////////////////////////////////////////////////////////////////////////
	// Enum Section

	/// <summary>
	/// Socket Event Enum
	/// </summary>
	enum class ESocketNotify : int
	{
		SOCKET_NOTIFY_PACKET = 0,	// Recv Packet
		SOCKET_NOTIFY_CONNECT,		// Socket Connected
		SOCKET_NOTIFY_CLOSED,		// Socket Closed
	};

	/// <summary>
	/// Socket Close Reason
	/// </summary>
	enum class ENetworkResult : int
	{
		NETWORK_RESULT_OK = 0,								// 이상없음.
		NETWORK_RESULT_SERVER_RELEASE,						// IOCP 서버 서비스 종료
		NETWORK_RESULT_CANNOT_CREATE_IOCP_PEER,				// Listener에서 Peer Socket에 대한 IOCP 생성 실패
		NETWORK_RESULT_SOCKET_CLOSED,						// Read 작업 수행시, 이미 Socket 이 Closed 됨
		NETWORK_RESULT_NO_OVERLAPPED_DATA,					// Read 작업 수행시, IOCP에서 작업 완료된 패킷이 나오지 않은 상태.
		NETWORK_RESULT_IOCP_WORK_FAILED,					// Read 작업 수행시, IOCP 작업 실패
		NETWORK_RESULT_NO_DATA_READ,						// Read 작업 수행시, 읽어들인 데이터가 없음.
		NETWORK_RESULT_CANNOT_SEND_ENOUGH,					// Write 작업 수행시, 버퍼 세팅 데이터보다 못보냄.
		NETWORK_RESULT_RECV_ERROR,							// 세션 Read 작업 수행시 에러발생
		NETWORK_RESULT_SEND_ERROR,							// 세션 Write 작업 수행시 에러발생
		NETWORK_RESULT_IOCPSOCKET_DESTROYED,				// 세션 클래스 소멸자.
		NETWORK_RESULT_CLOSE_BY_APPLICATION,				// 응용프로그램에서 프로그래머에 의해 연결 종료
	};


}


////////////////////////////////////////////////////////////////////////////////
// Inline Function Section

inline int GetNetworkError()
{
	int nRet = GetLastError();
	SetLastError(0);
	return nRet;
}


