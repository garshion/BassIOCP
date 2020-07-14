#include "SystemInfoManager.h"
#include <Windows.h>

Bass::SystemInfoManager Bass::SystemInfoManager::m_Instance;

Bass::SystemInfoManager::~SystemInfoManager()
{
}

Bass::SystemInfoManager & Bass::SystemInfoManager::GetInstance()
{
	return m_Instance;
}

int Bass::SystemInfoManager::GetProcessorCount()
{
#ifdef _MSC_VER
#	if (_MSC_VER <= 1900)		// Visual Studio 2015 이하만 작동
		SYSTEM_INFO	si;
		GetSystemInfo(&si);
		return si.dwNumberOfProcessors;
#	endif
#endif
	return 1;

}

Bass::SystemInfoManager::SystemInfoManager()
{
}
