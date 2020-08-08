#include "LogManagerImpl.hxx"
#include "BassCommon.h"
#include <thread>
#include "Console.h"
#include <fstream>
#include <iostream>

Bass::LogManagerImpl::LogManagerImpl()
{
}

Bass::LogManagerImpl::~LogManagerImpl()
{
}

void Bass::LogManagerImpl::SetPath(const std::wstring& strDir, const std::wstring& strFileName)
{
	if (false == strDir.empty())
		m_LogDirPath.assign(strDir);

	if (true == strFileName.empty())
		return;

	m_LogFilePath = m_LogDirPath.c_str();
	m_LogFilePath.append(strFileName);
}

void Bass::LogManagerImpl::SetLogPath(const std::wstring& strLogPath)
{
	if (true == strLogPath.empty())
		return;
	m_LogDirPath.assign(strLogPath);
}

void Bass::LogManagerImpl::SetLogFileName(const std::wstring& strLogFileName)
{
	if (true == strLogFileName.empty())
		return;
	m_LogFilePath = m_LogDirPath.c_str();
	m_LogFilePath.append(strLogFileName);
}

void Bass::LogManagerImpl::SetLogWriteTickDelayMS(const int& nLogTickMS)
{
	if (nLogTickMS <= 0)
		return;
	m_nLogWriteTickDelayMS = nLogTickMS;
}

void Bass::LogManagerImpl::SetLogFileMaxSize(const size_t& nLogFileMaxSize)
{
	if (nLogFileMaxSize < DEFAULT_LOG_FILE_MIN_SIZE)
		return;
	m_nMaxLogFileSize = nLogFileMaxSize;
}

void Bass::LogManagerImpl::Start()
{
	if (true == m_bRunning.load())
		return;
	if (nullptr != m_pThread)
		return;

	_MakeFolder();
	_ChangeAndClearFile();

	m_bRunning.store(true);
	m_pThread = new std::thread(&Bass::LogManagerImpl::_Run, this);
	m_pThread->detach();
}

void Bass::LogManagerImpl::Stop()
{
	m_bRunning.store(false);
}

void Bass::LogManagerImpl::Log(const std::wstring& log, const ELogLevel& level)
{
	m_LogQueue.Push(LogData(level, log));
}

void Bass::LogManagerImpl::_MakeFolder()
{
	if (true == std::filesystem::exists(m_LogDirPath))
	{
		if (true == std::filesystem::is_directory(m_LogDirPath))
			return;
	}

	std::error_code ec;
	if (false == std::filesystem::create_directories(m_LogDirPath, ec))
	{
		// error occures

	}

}

bool Bass::LogManagerImpl::_CheckFileChangable()
{
	if (false == std::filesystem::exists(m_LogFilePath))
		return false;

	auto nSize = std::filesystem::file_size(m_LogFilePath);
	if (nSize > m_nMaxLogFileSize)
		return true;
	return false;
}

void Bass::LogManagerImpl::_ChangeAndClearFile()
{
	if (false == std::filesystem::exists(m_LogFilePath))
		return;

	auto nTick = std::chrono::system_clock::now().time_since_epoch().count();
	std::wstring strNewExt(L".");
	strNewExt.append(std::to_wstring(nTick));

	std::filesystem::path renamePath(m_LogFilePath);
	renamePath.replace_extension(strNewExt);

	std::filesystem::rename(m_LogFilePath, renamePath);
}

void Bass::LogManagerImpl::_Run()
{
	if (nullptr == m_pThread)
		return;

	std::queue<LogData> logList;
	std::chrono::system_clock::time_point untilTime = std::chrono::system_clock::now() + std::chrono::milliseconds(0);

	while (m_bRunning.load())
	{
		m_LogQueue.MoveAll(logList);

		if (false == logList.empty())
		{
			std::wstring strLogFile = m_LogFilePath.wstring();
			std::ofstream fsLog(strLogFile.c_str(), std::ios::app);

			while (false == logList.empty())
			{
				auto& data = logList.front();
				if (true == _IsWriteType(data.LogLevel))
					fsLog << data.ToString().c_str() << std::endl;

				_ChangeConsoleColor(data.LogLevel);
				std::wcout << data.ToString().c_str() << std::endl;

				logList.pop();
			}

			Console::ChangeConsoleColor();
			if (true == _CheckFileChangable())
				_ChangeAndClearFile();
		}

		untilTime += std::chrono::milliseconds(m_nLogWriteTickDelayMS);
		std::this_thread::sleep_until(untilTime);
	}

	SafeDelete(m_pThread);
}

void Bass::LogManagerImpl::_ChangeConsoleColor(const ELogLevel& level)
{
	switch (level)
	{
	case ELogLevel::Warning:
		Console::ChangeConsoleColor(EConsoleColor::Yellow);
		break;
	case ELogLevel::Error:
		Console::ChangeConsoleColor(EConsoleColor::Red);
		break;
	case ELogLevel::Debug:
		Console::ChangeConsoleColor(EConsoleColor::LightCyan);
		break;
	case ELogLevel::System:
		Console::ChangeConsoleColor(EConsoleColor::LightGreen);
		break;
	case ELogLevel::Console:
	case ELogLevel::Info:
	default:
		Console::ChangeConsoleColor();
		break;
	}
}

bool Bass::LogManagerImpl::_IsWriteType(const ELogLevel& level)
{
	switch (level)
	{
	case ELogLevel::Info:
	case ELogLevel::Warning:
	case ELogLevel::Error:
	case ELogLevel::Debug:
	case ELogLevel::System:
		return true;
	default:
		break;
	}

	return false;
}
