#pragma once
namespace Bass
{
	class SystemInfoManager
	{

	public:
		~SystemInfoManager();
		static SystemInfoManager& GetInstance();

		int GetProcessorCount();

		// CPU ����
		// CPU ��뷮
		// �޸� ��뷮
		// ��Ʈ��ũ ��뷮��.... �����Ϸ���



	private:
		SystemInfoManager();

	private:
		static SystemInfoManager m_Instance;


	};

}