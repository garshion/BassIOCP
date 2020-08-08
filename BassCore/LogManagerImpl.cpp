#include "LogManagerImpl.hxx"
#include "BassCommon.h"
#include <thread>
#include <filesystem>
#include "Console.h"
#include <fstream>
#include <iostream>

Bass::LogManagerImpl::LogManagerImpl()
{
}

Bass::LogManagerImpl::~LogManagerImpl()
{
}

void Bass::LogManagerImpl::SetLogPath(const std::wstring& strLogPath)
{
	if (true == strLogPath.empty())
		return;
	m_strLogPath.assign(strLogPath.begin(), strLogPath.end());
}

void Bass::LogManagerImpl::SetLogFileName(const std::wstring& strLogFileName)
{
	if (true == strLogFileName.empty())
		return;
	m_strLogFileName.assign(strLogFileName.begin(), strLogFileName.end());
}

//void Bass::LogManagerImpl::SetLogPoolSize(const size_t& nLogPoolSize)
//{
//	if (nLogPoolSize == 0)
//		return;
//	m_nLogPoolSize = nLogPoolSize;
//}

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


	m_bRunning.store(true);
	m_pThread = new std::thread(&Bass::LogManagerImpl::_Run, this);
	m_pThread->detach();
}

void Bass::LogManagerImpl::Stop()
{
	m_bRunning.store(false);
}

void Bass::LogManagerImpl::_MakeFolder()
{
	std::filesystem::path checkFolder(m_strLogPath);
	if (true == std::filesystem::exists(checkFolder))
	{
		if (true == std::filesystem::is_directory(checkFolder))
			return;
	}

	std::error_code ec;
	if (false == std::filesystem::create_directories(m_strLogPath, ec))
	{
		// error occures
		
	}

}

void Bass::LogManagerImpl::_ChangeAndClearFile()
{




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
			std::wstring strLogFile = m_strLogPath + L"/" + m_strLogFileName;
			std::ofstream fsLog(strLogFile.c_str(), std::ios::app);

			while (false == logList.empty())
			{
				auto& data = logList.front();
				if (true == _IsWriteType(data.LogLevel))
					fsLog << data.ToString().c_str() << std::endl;

				_ChangeConsoleColor(data.LogLevel);
				std::wcout << data.ToString().c_str() << std::endl;
			}

			Console::ChangeConsoleColor();
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
