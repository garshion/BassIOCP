#pragma once
#include "Singleton.h"
#include <string>

namespace Bass
{
	constexpr const wchar_t* DEFAULT_LOG_PATH = L"./Log/";					// �⺻ �α� ���� ���
	constexpr const wchar_t* DEFAULT_LOG_FILENAME = L"System.log";			// �⺻ �α� ���ϸ�

	constexpr size_t DEFAULT_LOG_FILE_MAX_SIZE = 10 * 1024 * 1024;			// �α����� �ִ� ũ�� (����)
	constexpr int DEFAULT_LOG_WRITE_TICK_DELAY_MS = 50;						// �α� Thread sleep �ð�

	constexpr size_t VARIABLE_FORMAT_BUFFER_SIZE = 1024;					// �������� ���� ũ��

	class LogManagerImpl;
	class LogManager : public Singleton<LogManager>
	{
	public:
		LogManager();
		~LogManager();

		void SetPath(const std::wstring& strDir = DEFAULT_LOG_PATH, const std::wstring& strFileName = DEFAULT_LOG_FILENAME);
		void SetLogPath(const std::wstring& strLogPath = DEFAULT_LOG_PATH);
		void SetLogFileName(const std::wstring& strLogFileName = DEFAULT_LOG_FILENAME);
		void SetLogWriteTickDelayMS(const int& nLogTickMS = DEFAULT_LOG_WRITE_TICK_DELAY_MS);
		void SetLogFileMaxSize(const size_t& nLogFileMaxSize = DEFAULT_LOG_FILE_MAX_SIZE);

		void Start();
		void Stop();

		void Info(const wchar_t* format, ...);
		void Warning(const wchar_t* format, ...);
		void Error(const wchar_t* format, ...);
		void Debug(const wchar_t* format, ...);
		void Console(const wchar_t* format, ...);
		void System(const wchar_t* format, ...);

	private:
		LogManagerImpl* m_pLogManager = nullptr;
	};
}