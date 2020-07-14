#pragma once
namespace Bass
{
	class SystemInfoManager
	{

	public:
		~SystemInfoManager();
		static SystemInfoManager& GetInstance();

		int GetProcessorCount();

	private:
		SystemInfoManager();

	private:
		static SystemInfoManager m_Instance;


	};

}