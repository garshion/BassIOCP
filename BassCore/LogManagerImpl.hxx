#pragma once
#include "LogData.h"
#include <atomic>
//#include <thread>
#include <vector>
#include "MTQueue.h"

namespace std
{
	class thread;
}

namespace Bass
{
	constexpr const wchar_t* DEFAULT_LOG_PATH			= L"./Log/";		// �⺻ �α� ���� ���
	constexpr const wchar_t* DEFAULT_LOG_FILENAME		= L"System.log";	// �⺻ �α� ���ϸ�
	
	//constexpr size_t DEFAULT_LOG_POOL_SIZE = 2000;							// �α� Ǯ ������
	constexpr size_t DEFAULT_LOG_FILE_MAX_SIZE = 10 * 1024 * 1024;			// �α����� �ִ� ũ�� (����)
	constexpr size_t DEFAULT_LOG_FILE_MIN_SIZE = 10 * 1024;					// �α� ���� �ּ� ũ��
	constexpr int DEFAULT_LOG_WRITE_TICK_DELAY_MS = 50;						// �α� Thread sleep �ð�



	class LogManagerImpl
	{
	public:
		LogManagerImpl();
		~LogManagerImpl();

		// Setting
		void SetLogPath(const std::wstring& strLogPath = DEFAULT_LOG_PATH);
		void SetLogFileName(const std::wstring& strLogFileName = DEFAULT_LOG_FILENAME);
		//void SetLogPoolSize(const size_t& nLogPoolSize = DEFAULT_LOG_POOL_SIZE);
		void SetLogWriteTickDelayMS(const int& nLogTickMS = DEFAULT_LOG_WRITE_TICK_DELAY_MS);
		void SetLogFileMaxSize(const size_t& nLogFileMaxSize = DEFAULT_LOG_FILE_MAX_SIZE);


		// Control
		void Start();
		void Stop();

		// Write

	private:
		void _MakeFolder();				// �α� ���� ����
		void _ChangeAndClearFile();		// ���� �α� ���ϸ� ���� (���� ũ�� split)


		void _Run();

		void _ChangeConsoleColor(const ELogLevel& level);
		bool _IsWriteType(const ELogLevel& level);


	private:
		std::wstring m_strLogPath = DEFAULT_LOG_PATH;
		std::wstring m_strLogFileName = DEFAULT_LOG_FILENAME;

		//size_t	m_nLogPoolSize = DEFAULT_LOG_POOL_SIZE;
		int		m_nLogWriteTickDelayMS = DEFAULT_LOG_WRITE_TICK_DELAY_MS;

		size_t	m_nMaxLogFileSize = DEFAULT_LOG_FILE_MAX_SIZE;

		//std::vector<LogData> m_vecLogData;
		MTQueue<LogData> m_LogQueue;


		std::atomic_bool m_bRunning = false;
		std::thread* m_pThread = nullptr;

	};

}