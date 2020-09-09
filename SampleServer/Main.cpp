#include <LogManager.h>
#include <thread>
#include "SampleServer.h"


int main(void)
{
	Bass::LogManager::GetInstance().Start();

	Bass::LogManager::GetInstance().System(L"Sample Server Start!!");

	SampleServer server;
	server.Start();

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}


	Bass::LogManager::GetInstance().Stop();
	return 0;
}