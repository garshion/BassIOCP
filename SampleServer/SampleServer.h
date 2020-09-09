#pragma once
#include <IOCP.h>

class SampleServer
{
public:
	SampleServer();
	~SampleServer();

	void Start();


private:
	bool _PacketProcess(int nIndex, Bass::Packet& packet);

	void _OnConnect(int nIndex);
	void _OnDisconnect(int nIndex);


	void _Run();

private:
	Bass::CIOCP m_ServerSocket;

	bool m_bRunning = false;
};

