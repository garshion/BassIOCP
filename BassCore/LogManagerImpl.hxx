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
	constexpr const wchar_t* DEFAULT_LOG_PATH			= L"./Log/";		// 기본 로그 폴더 경로
	constexpr const wchar_t* DEFAULT_LOG_FILENAME		= L"System.log";	// 기본 로그 파일명
	
	//constexpr size_t DEFAULT_LOG_POOL_SIZE = 2000;							// 로그 풀 사이즈
	constexpr size_t DEFAULT_LOG_FILE_MAX_SIZE = 10 * 1024 * 1024;			// 로그파일 최대 크기 (분할)
	constexpr size_t DEFAULT_LOG_FILE_MIN_SIZE = 10 * 1024;					// 로그 파일 최소 크기
	constexpr int DEFAULT_LOG_WRITE_TICK_DELAY_MS = 50;						// 로그 Thread sleep 시간



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
		void _MakeFolder();				// 로그 폴더 생성
		void _ChangeAndClearFile();		// 기존 로그 파일명 변경 (파일 크기 split)


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