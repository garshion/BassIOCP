#include "PacketResolver.hxx"

Bass::PacketResolver::PacketResolver()
{
	m_pBuffer = new char[MAX_BUFFER_SIZE];
	_ClearBuffer();
}

Bass::PacketResolver::~PacketResolver()
{
	SafeDeleteArray(m_pBuffer);
}

void Bass::PacketResolver::SetSocketIndex(const SocketIndex_t& socketIndex)
{
	m_PacketData.nSenderIndex = socketIndex;
}

bool Bass::PacketResolver::Resolve(char * pBuffer, int nLength, int & nUsedBytes)
{
	m_IsCompleted = false;

	if (nullptr == pBuffer
		|| 0 >= nLength
		|| 0 > nUsedBytes)
		return false;

	// 헤더가 완성되지 않았을 경우
	if (m_nRemainHeaderSize > 0)
	{
		if (m_nRemainHeaderSize > PACKET_HEADER_SIZE)
			return false;

		// 받은 데이터가 헤더를 완섣성하기에 충분할 경우
		if (m_nRemainHeaderSize <= nLength)
		{
			memcpy_s(m_PacketData.pData + PACKET_HEADER_SIZE - m_nRemainHeaderSize, m_nRemainHeaderSize, pBuffer, m_nRemainHeaderSize);
			pBuffer += m_nRemainHeaderSize;
			nLength -= m_nRemainHeaderSize;
			nUsedBytes += m_nRemainHeaderSize;
			m_nRemainHeaderSize = 0;

			if (MAX_PACKET_SIZE < m_PacketData.GetSize()
				|| PACKET_HEADER_SIZE > m_PacketData.GetSize())
				return false;	// 유효하지 않은 패킷

			m_nCurrentOffset = PACKET_HEADER_SIZE;
		}
		// 받은 데이터가 헤더를 완섣성하기에 부족할 경우
		else
		{
			memcpy_s(m_PacketData.pData + PACKET_HEADER_SIZE - m_nRemainHeaderSize, m_nRemainHeaderSize, pBuffer, nLength);
			nUsedBytes += nLength;
			m_nRemainHeaderSize -= nLength;
			m_nCurrentOffset = PACKET_HEADER_SIZE - m_nRemainHeaderSize;
			return true;
		}
	}
	// 남은 헤더값도 없고 패킷 사이즈도 0일 경우 (다 처리되고 나서 처음 받는 패킷일 경우)
	else if (0 == m_nPacketSize)
	{
		_ClearBuffer();
		m_nRemainHeaderSize = PACKET_HEADER_SIZE;
		return Resolve(pBuffer, nLength, nUsedBytes);
	}


	m_nPacketSize = m_PacketData.GetSize();	// 완성해야할 전체 패킷 크기 설정

	nLength = min(m_nPacketSize - m_nCurrentOffset, nLength);	// 완성 가능하면, 완성 가능한 크기만큼으로만 버퍼 길이 설정.

	if (nLength > 0)
	{
		memcpy_s(m_PacketData.pData + m_nCurrentOffset, MAX_PACKET_SIZE - m_nCurrentOffset, pBuffer, nLength);
		m_nCurrentOffset += nLength;
		nUsedBytes += nLength;
	}

	// 패킷이 완성되었을 경우
	if (m_nCurrentOffset == m_nPacketSize)
	{
		AutoLock(m_Lock);
		m_IsCompleted = true;
		_ClearBuffer();
	}
	return true;
}

Bass::Packet & Bass::PacketResolver::GetReceivedPacket()
{
	return m_PacketData;
}

bool Bass::PacketResolver::IsCompleted() const
{
	return m_IsCompleted;
}


void Bass::PacketResolver::_ClearBuffer()
{
	if (nullptr == m_pBuffer)
		return;
	memset(m_pBuffer, 0x00, MAX_BUFFER_SIZE);
	m_nRemainHeaderSize = m_nPacketSize = m_nCurrentOffset = 0;
}
