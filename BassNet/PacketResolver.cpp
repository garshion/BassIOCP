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

	// ����� �ϼ����� �ʾ��� ���
	if (m_nRemainHeaderSize > 0)
	{
		if (m_nRemainHeaderSize > PACKET_HEADER_SIZE)
			return false;

		// ���� �����Ͱ� ����� �ϼ����ϱ⿡ ����� ���
		if (m_nRemainHeaderSize <= nLength)
		{
			memcpy_s(m_PacketData.pData + PACKET_HEADER_SIZE - m_nRemainHeaderSize, m_nRemainHeaderSize, pBuffer, m_nRemainHeaderSize);
			pBuffer += m_nRemainHeaderSize;
			nLength -= m_nRemainHeaderSize;
			nUsedBytes += m_nRemainHeaderSize;
			m_nRemainHeaderSize = 0;

			if (MAX_PACKET_SIZE < m_PacketData.GetSize()
				|| PACKET_HEADER_SIZE > m_PacketData.GetSize())
				return false;	// ��ȿ���� ���� ��Ŷ

			m_nCurrentOffset = PACKET_HEADER_SIZE;
		}
		// ���� �����Ͱ� ����� �ϼ����ϱ⿡ ������ ���
		else
		{
			memcpy_s(m_PacketData.pData + PACKET_HEADER_SIZE - m_nRemainHeaderSize, m_nRemainHeaderSize, pBuffer, nLength);
			nUsedBytes += nLength;
			m_nRemainHeaderSize -= nLength;
			m_nCurrentOffset = PACKET_HEADER_SIZE - m_nRemainHeaderSize;
			return true;
		}
	}
	// ���� ������� ���� ��Ŷ ����� 0�� ��� (�� ó���ǰ� ���� ó�� �޴� ��Ŷ�� ���)
	else if (0 == m_nPacketSize)
	{
		_ClearBuffer();
		m_nRemainHeaderSize = PACKET_HEADER_SIZE;
		return Resolve(pBuffer, nLength, nUsedBytes);
	}


	m_nPacketSize = m_PacketData.GetSize();	// �ϼ��ؾ��� ��ü ��Ŷ ũ�� ����

	nLength = min(m_nPacketSize - m_nCurrentOffset, nLength);	// �ϼ� �����ϸ�, �ϼ� ������ ũ�⸸ŭ���θ� ���� ���� ����.

	if (nLength > 0)
	{
		memcpy_s(m_PacketData.pData + m_nCurrentOffset, MAX_PACKET_SIZE - m_nCurrentOffset, pBuffer, nLength);
		m_nCurrentOffset += nLength;
		nUsedBytes += nLength;
	}

	// ��Ŷ�� �ϼ��Ǿ��� ���
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
