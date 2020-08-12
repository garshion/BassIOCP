#pragma once
#include "LogData.h"
#include <atomic>
#include <vector>
#include "MTQueue.h"
#include <filesystem>

namespace std
{
	class thread;
}

namespace Bass
{
	constexpr size_t DEFAULT_LOG_FILE_MIN_SIZE = 10 * 1024;					// 로그 파일 최소 크기

	class LogManagerImpl
	{
	public:
		LogManagerImpl();
		~LogManagerImpl();

		// Setting
		void SetPath(const std::wstring& strDir, const std::wstring& strFileName);
		void SetLogPath(const std::wstring& strLogPath);
		void SetLogFileName(const std::wstring& strLogFileName);
		void SetLogWriteTickDelayMS(const int& nLogTickMS);
		void SetLogFileMaxSize(const size_t& nLogFileMaxSize);


		// Control
		void Start();
		void Stop();

		// Write
		void Log(const std::wstring& log, const ELogLevel& level);

		void ShowConsole(const bool& bShow);

	private:
		void _MakeFolder();				// 로그 폴더 생성
		bool _CheckFileChangable();		// 파일 크기를 검사하여 파일을 바꿔줘야 하는지
		void _ChangeAndClearFile();		// 기존 로그 파일명 변경 (파일 크기 split)

		void _Run();

		void _ChangeConsoleColor(const ELogLevel& level);
		bool _IsWriteType(const ELogLevel& level);

	private:
		// 기본값을 밖에서 사용해서 여기는 하드코딩.
		int		m_nLogWriteTickDelayMS = 50;	
		size_t	m_nMaxLogFileSize = 10 * 1024 * 1024;;
		std::filesystem::path m_LogDirPath = L"./Log/";
		std::filesystem::path m_LogFilePath = L"System.log";
		// end, 하드코딩

		MTQueue<LogData> m_LogQueue;

		std::atomic_bool m_bShowConsole = true;
		std::atomic_bool m_bRunning = false;
		std::thread* m_pThread = nullptr;


	};

}