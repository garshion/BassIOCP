#pragma once
namespace Bass
{
	class SystemInfoManager
	{

	public:
		~SystemInfoManager();
		static SystemInfoManager& GetInstance();

		int GetProcessorCount();

		// CPU 갯수
		// CPU 사용량
		// 메모리 사용량
		// 네트워크 사용량은.... 가능하려나



	private:
		SystemInfoManager();

	private:
		static SystemInfoManager m_Instance;


	};

}