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
	constexpr size_t DEFAULT_LOG_FILE_MIN_SIZE = 10 * 1024;					// �α� ���� �ּ� ũ��

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
		void _MakeFolder();				// �α� ���� ����
		bool _CheckFileChangable();		// ���� ũ�⸦ �˻��Ͽ� ������ �ٲ���� �ϴ���
		void _ChangeAndClearFile();		// ���� �α� ���ϸ� ���� (���� ũ�� split)

		void _Run();

		void _ChangeConsoleColor(const ELogLevel& level);
		bool _IsWriteType(const ELogLevel& level);

	private:
		// �⺻���� �ۿ��� ����ؼ� ����� �ϵ��ڵ�.
		int		m_nLogWriteTickDelayMS = 50;	
		size_t	m_nMaxLogFileSize = 10 * 1024 * 1024;;
		std::filesystem::path m_LogDirPath = L"./Log/";
		std::filesystem::path m_LogFilePath = L"System.log";
		// end, �ϵ��ڵ�

		MTQueue<LogData> m_LogQueue;

		std::atomic_bool m_bShowConsole = true;
		std::atomic_bool m_bRunning = false;
		std::thread* m_pThread = nullptr;


	};

}