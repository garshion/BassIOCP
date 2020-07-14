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


	// ��Ŷ �԰�
#if defined USE_JUMBO_PACKET
	constexpr size_t MAX_PACKET_SIZE = 8000;	// Using Jumbo Packet 
#else
	constexpr size_t MAX_PACKET_SIZE = 1440;	// MTU 1500 - TCP Header size 20 - Tcp Header Option Size 40
#endif

	constexpr size_t PACKET_PROTOCOL_SIZE = sizeof(ProtocolSize_t);
	constexpr size_t PACKET_LENGTH_SIZE = sizeof(LengthSize_t);
	constexpr size_t PACKET_HEADER_SIZE = PACKET_LENGTH_SIZE + PACKET_PROTOCOL_SIZE;

	// ��Ʈ��ũ �⺻��
	constexpr size_t MAX_BUFFER_SIZE = MAX_PACKET_SIZE * 2;
	constexpr size_t DEFAULT_SESSION_COUNT = 5000;		



	// IOCP ����
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
		NETWORK_RESULT_OK = 0,								// �̻����.
		NETWORK_RESULT_SERVER_RELEASE,						// IOCP ���� ���� ����
		NETWORK_RESULT_CANNOT_CREATE_IOCP_PEER,				// Listener���� Peer Socket�� ���� IOCP ���� ����
		NETWORK_RESULT_SOCKET_CLOSED,						// Read �۾� �����, �̹� Socket �� Closed ��
		NETWORK_RESULT_NO_OVERLAPPED_DATA,					// Read �۾� �����, IOCP���� �۾� �Ϸ�� ��Ŷ�� ������ ���� ����.
		NETWORK_RESULT_IOCP_WORK_FAILED,					// Read �۾� �����, IOCP �۾� ����
		NETWORK_RESULT_NO_DATA_READ,						// Read �۾� �����, �о���� �����Ͱ� ����.
		NETWORK_RESULT_CANNOT_SEND_ENOUGH,					// Write �۾� �����, ���� ���� �����ͺ��� ������.
		NETWORK_RESULT_RECV_ERROR,							// ���� Read �۾� ����� �����߻�
		NETWORK_RESULT_SEND_ERROR,							// ���� Write �۾� ����� �����߻�
		NETWORK_RESULT_IOCPSOCKET_DESTROYED,				// ���� Ŭ���� �Ҹ���.
		NETWORK_RESULT_CLOSE_BY_APPLICATION,				// �������α׷����� ���α׷��ӿ� ���� ���� ����
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


