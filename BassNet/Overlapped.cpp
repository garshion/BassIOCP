#include "Overlapped.hxx"

Bass::COverlapped::COverlapped(const EOperationMode & eMode, const EOverlappedType & eType)
{
	m_Type = eType;
	m_Mode = eMode;
	Reset();
}

Bass::COverlapped::~COverlapped()
{
}

const Bass::EOperationMode & Bass::COverlapped::Mode() const
{
	return m_Mode;
}

const Bass::EOverlappedType & Bass::COverlapped::Type() const
{
	return m_Type;
}

WSABUF & Bass::COverlapped::GetBuffer()
{
	return m_WSABuf;
}

bool Bass::COverlapped::AddData(SSendedOverlappedInfo * pInfo, char * pData, const size_t& nSize)
{
	if (nullptr == pData
		|| nullptr == pInfo
		|| nSize <= 0
		|| m_WSABuf.len + nSize > MAX_PACKET_SIZE)
		return false;

	pInfo->pOver = this;
	pInfo->pData = &m_pBuffer[m_WSABuf.len];
	memcpy_s(&m_pBuffer[m_WSABuf.len], sizeof(m_pBuffer) - m_WSABuf.len, pData, nSize);
	m_WSABuf.len += (ULONG)nSize;

	return true;
}

int Bass::COverlapped::GetDataSize()
{
	return m_WSABuf.len;
}

void Bass::COverlapped::Reset()
{
	// OVERLAPPED
	Internal = 0;
	InternalHigh = 0;
	Offset = 0;
	OffsetHigh = 0;
	hEvent = NULL;

	memset(m_pBuffer, 0x00, sizeof(m_pBuffer));
	m_WSABuf.buf = m_pBuffer;
	m_WSABuf.len = Mode() == EOperationMode::OPERATION_MODE_READ ? sizeof(m_pBuffer) : 0;
}
