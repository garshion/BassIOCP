#include <LogManager.h>
#include <thread>
#include "SampleServer.h"


int main(void)
{
	Bass::LogManager::Instance.Start();

	Bass::LogManager::Instance.System(L"Sample Server Start!!");

	SampleServer server;
	server.Start();

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}


	Bass::LogManager::Instance.Stop();
	return 0;
}