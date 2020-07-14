#include "NetworkCore.h"
#include "NetworkCommon.h"


Bass::NetworkCore Bass::NetworkCore::m_Instance;

Bass::NetworkCore::~NetworkCore()
{
	CleanSocket();
}

Bass::NetworkCore & Bass::NetworkCore::GetInstance()
{
	return m_Instance;
}

void Bass::NetworkCore::InitSocket()
{
	if (true == m_IsWinsockInit)
		return;

	WSADATA WsaData;
	m_IsWinsockInit = (WSAStartup(MAKEWORD(2, 2), &WsaData) == 0);
}

void Bass::NetworkCore::CleanSocket()
{
	if (true == m_IsWinsockInit)
	{
		WSACleanup();
		m_IsWinsockInit = false;
	}
}

bool Bass::NetworkCore::IsError(int nErrorCode)
{
	if (0 == nErrorCode)
	{
		nErrorCode = WSAGetLastError();
		WSASetLastError(0);
	}

	// From MSDN
	switch (nErrorCode)
	{
	case 0:
	case WSA_IO_INCOMPLETE:			// 996L Overlapped I/O event is not in a signaled state.
	case WSA_IO_PENDING:			// 997L Overlapped I/O operation is in progress.
		break;
	case WSA_INVALID_HANDLE:		// 6L The handle is invalid.
	case WSA_NOT_ENOUGH_MEMORY:		// 8L Not enough storage is available to process this command.
	case ERROR_NETNAME_DELETED:		// 64L The specified network name is no longer available.
	case WSA_INVALID_PARAMETER:		// 87L The parameter is incorrect.
	case WSA_OPERATION_ABORTED:		// 995L The I/O operation has been aborted because of either a thread exit or an application request.
	case WSAEINTR:					// 10004 A blocking operation was interrupted by a call to WSACancelBlockingCall.
	case WSAEBADF:					// 10009 The file handle supplied is not valid.
	case WSAEACCES:					// 10013 An attempt was made to access a socket in a way forbidden by its access permissions.
	case WSAEFAULT:					// 10014 The system detected an invalid pointer address in attempting to use a pointer argument in a call.
	case WSAEINVAL:					// 10022 An invalid argument was supplied.
	case WSAEMFILE:					// 10024 Too many open sockets.
	case WSAEWOULDBLOCK:			// 10035 A non-blocking socket operation could not be completed immediately.
	case WSAEINPROGRESS:			// 10036 A blocking operation is currently executing.
	case WSAEALREADY:				// 10037 An operation was attempted on a non-blocking socket that already had an operation in progress.
	case WSAENOTSOCK:				// 10038 An operation was attempted on something that is not a socket.
	case WSAEDESTADDRREQ:			// 10039 A required address was omitted from an operation on a socket.
	case WSAEMSGSIZE:				// 10040 A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram into was smaller than the datagram itself.
	case WSAEPROTOTYPE:				// 10041 A protocol was specified in the socket function call that does not support the semantics of the socket type requested.
	case WSAENOPROTOOPT:			// 10042 An unknown, invalid, or unsupported option or level was specified in a getsockopt or setsockopt call.
	case WSAEPROTONOSUPPORT:		// 10043 The requested protocol has not been configured into the system, or no implementation for it exists.
	case WSAESOCKTNOSUPPORT:		// 10044 The support for the specified socket type does not exist in this address family.
	case WSAEOPNOTSUPP:				// 10045 The attempted operation is not supported for the type of object referenced.
	case WSAEPFNOSUPPORT:			// 10046 The protocol family has not been configured into the system or no implementation for it exists.
	case WSAEAFNOSUPPORT:			// 10047 An address incompatible with the requested protocol was used.
	case WSAEADDRINUSE:				// 10048 Only one usage of each socket address (protocol/network address/port) is normally permitted.
	case WSAEADDRNOTAVAIL:			// 10049 The requested address is not valid in its context.
	case WSAENETDOWN:				// 10050 A socket operation encountered a dead network.
	case WSAENETUNREACH:			// 10051 A socket operation was attempted to an unreachable network.
	case WSAENETRESET:				// 10052 The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress.
	case WSAECONNABORTED:			// 10053 An established connection was aborted by the software in your host machine.
	case WSAECONNRESET:				// 10054 An existing connection was forcibly closed by the remote host.
	case WSAENOBUFS:				// 10055 An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.
	case WSAEISCONN:				// 10056 A connect request was made on an already connected socket.
	case WSAENOTCONN:				// 10057 A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using a sendto call) no address was supplied.
	case WSAESHUTDOWN:				// 10058 A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call.
	case WSAETOOMANYREFS:			// 10059 Too many references to some kernel object.
	case WSAETIMEDOUT:				// 10060 A connection attempt failed because the connected party did not properly respond after a period of time, or established connection failed because connected host has failed to respond.
	case WSAECONNREFUSED:			// 10061 No connection could be made because the target machine actively refused it.
	case WSAELOOP:					// 10062 Cannot translate name.
	case WSAENAMETOOLONG:			// 10063 Name component or name was too long.
	case WSAEHOSTDOWN:				// 10064 A socket operation failed because the destination host was down.
	case WSAEHOSTUNREACH:			// 10065 A socket operation was attempted to an unreachable host.
	case WSAENOTEMPTY:				// 10066 Cannot remove a directory that is not empty.
	case WSAEPROCLIM:				// 10067 A Windows Sockets implementation may have a limit on the number of applications that may use it simultaneously.
	case WSAEUSERS:					// 10068 Ran out of quota.
	case WSAEDQUOT:					// 10069 Ran out of disk quota.
	case WSAESTALE:					// 10070 File handle reference is no longer available.
	case WSAEREMOTE:				// 10071 Item is not available locally.
	case WSASYSNOTREADY:			// 10091 WSAStartup cannot function at this time because the underlying system it uses to provide network services is currently unavailable.
	case WSAVERNOTSUPPORTED:		// 10092 The Windows Sockets version requested is not supported.
	case WSANOTINITIALISED:			// 10093 Either the application has not called WSAStartup, or WSAStartup failed.
	case WSAEDISCON:				// 10101 Returned by WSARecv or WSARecvFrom to indicate the remote party has initiated a graceful shutdown sequence.
	case WSAENOMORE:				// 10102 No more results can be returned by WSALookupServiceNext.
	case WSAECANCELLED:				// 10103 A call to WSALookupServiceEnd was made while this call was still processing. The call has been canceled.
	case WSAEINVALIDPROCTABLE:		// 10104 The procedure call table is invalid.
	case WSAEINVALIDPROVIDER:		// 10105 The requested service provider is invalid.
	case WSAEPROVIDERFAILEDINIT:	// 10106 The requested service provider could not be loaded or initialized.
	case WSASYSCALLFAILURE:			// 10107 A system call that should never fail has failed.
	case WSASERVICE_NOT_FOUND:		// 10108 No such service is known. The service cannot be found in the specified name space.
	case WSATYPE_NOT_FOUND:			// 10109 The specified class was not found.
	case WSA_E_NO_MORE:				// 10110 No more results can be returned by WSALookupServiceNext.
	case WSA_E_CANCELLED:			// 10111 A call to WSALookupServiceEnd was made while this call was still processing. The call has been canceled.
	case WSAEREFUSED:				// 10112 A database query failed because it was actively refused.
	case WSAHOST_NOT_FOUND:			// 11001 No such host is known.
	case WSATRY_AGAIN:				// 11002 This is usually a temporary error during hostname resolution and means that the local server did not receive a response from an authoritative server.
	case WSANO_RECOVERY:			// 11003 A non-recoverable error occurred during a database lookup.
	case WSANO_DATA:				// 11004 The requested name is valid, but no data of the requested type was found.
		return true;
	default:
		break;
	}
	return false;

}

Bass::NetworkCore::NetworkCore()
{
	InitSocket();
}
