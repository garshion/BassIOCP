#include <BassCore.h>
#include <thread>

using namespace Bass;

int main(void)
{
	// Log Å×½ºÆ®
	LogManager::GetInstance().SetLogFileMaxSize(10240);
	LogManager::GetInstance().SetLogPath(L"./Log/Test/");
	LogManager::GetInstance().SetLogFileName(L"TestLog.txt");

	LogManager::GetInstance().Start();

	for (int i = 0; i < 150; ++i)
	{
		LogManager::GetInstance().Info(L"Info Test...............................................................");
		LogManager::GetInstance().Warning(L"Warning Test............................................................");
		LogManager::GetInstance().Error(L"Error Test..............................................................");
		LogManager::GetInstance().Debug(L"Debug Test..............................................................");
		LogManager::GetInstance().Console(L"Console Test............................................................");
		LogManager::GetInstance().System(L"System Test.............................................................");
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

	}

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::duration<double>(1.0));
	}





	LogManager::GetInstance().Stop();
	return 0;
}