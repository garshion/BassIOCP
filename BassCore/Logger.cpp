#include "Logger.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "BassCommon.h"

Bass::Logger::Logger()
{
	m_LogPool.SetSize(DEFAULT_LOG_POOL_SIZE);
}

Bass::Logger::~Logger()
{
	Stop();
}


void Bass::Logger::SetLogPath(const std::string & strPath)
{
	m_strLogPath = strPath;
	_CheckAndMakeFolder();
}

void Bass::Logger::SetLogFileName(const std::string & strFileName)
{
	m_strLogFileName = strFileName;
}


void Bass::Logger::Info(const char* format, ...)
{
	char szBuffer[1024] = { 0, };
	va_list args;

	va_start(args, format);
	vsnprintf_s(szBuffer, sizeof(szBuffer), sizeof(szBuffer) - 1, format, args);
	va_end(args);

	Log(szBuffer, LOG_LEVEL_INFO);
}

void Bass::Logger::Warning(const char* format, ...)
{
	char szBuffer[1024] = { 0, };
	va_list args;

	va_start(args, format);
	vsnprintf_s(szBuffer, sizeof(szBuffer), sizeof(szBuffer) - 1, format, args);
	va_end(args);

	Log(szBuffer, LOG_LEVEL_WARN);
}

void Bass::Logger::Error(const char* format, ...)
{
	char szBuffer[1024] = { 0, };
	va_list args;

	va_start(args, format);
	vsnprintf_s(szBuffer, sizeof(szBuffer), sizeof(szBuffer) - 1, format, args);
	va_end(args);

	Log(szBuffer, LOG_LEVEL_ERROR);
}

void Bass::Logger::Debug([[maybe_unused]] const char* format, ...)
{
#ifdef _DEBUG
	char szBuffer[1024] = { 0, };
	va_list args;

	va_start(args, format);
	vsnprintf_s(szBuffer, sizeof(szBuffer), sizeof(szBuffer) - 1, format, args);
	va_end(args);

	Log(szBuffer, LOG_LEVEL_DEBUG);
#endif
}

void Bass::Logger::Console(const char* format, ...)
{
	char szBuffer[1024] = { 0, };
	va_list args;

	va_start(args, format);
	vsnprintf_s(szBuffer, sizeof(szBuffer), sizeof(szBuffer) - 1, format, args);
	va_end(args);

	std::cout << szBuffer << std::endl;
}



void Bass::Logger::Log(const std::string & log, ELogLevel level)
{
	SLogData* pData = m_LogPool.Pop();
	if (nullptr == pData)
		return;

	pData->logTime = time(nullptr);
	pData->level = level;
	pData->strLog = log;

	m_queueLog.Push(pData);
}



void Bass::Logger::Start()
{
	if (true == m_IsRunning)
		return;

	if (nullptr != m_pThread)
		return;

	m_IsRunning = true;
	m_pThread = new std::thread(&Logger::_Process, this);
	m_pThread->detach();
}

void Bass::Logger::Stop()
{
	m_IsRunning = false;
	SafeDelete(m_pThread);
}

const char * Bass::Logger::_GetLogLevelString(const ELogLevel& level) const
{
	switch (level)
	{
	case LOG_LEVEL_INFO: return "[INFO ]";
	case LOG_LEVEL_WARN: return "[WARN ]";
	case LOG_LEVEL_ERROR: return "[ERROR]";
	case LOG_LEVEL_DEBUG: return "[DEBUG]";
	default:
		break;
	}
	return "";
}

std::string Bass::Logger::_GetDateTimeString(const time_t & timeValue) const
{
	char temp[20] = { 0, };
	tm timeTM;
	errno_t nErr = localtime_s(&timeTM, &timeValue);
	if (nErr == 0)
	{
		strftime(temp, sizeof(temp), "%Y-%m-%d %H:%M:%S", &timeTM);
	}
	return std::string(temp);
}

std::string Bass::Logger::_GetDateString(const time_t & timeValue) const
{
	char temp[11] = { 0, };
	tm timeTM;
	errno_t nErr = localtime_s(&timeTM, &timeValue);
	if (nErr == 0)
	{
		strftime(temp, sizeof(temp), "%Y-%m-%d", &timeTM);
	}
	return std::string(temp);
}

void Bass::Logger::_CheckAndMakeFolder()
{
	if (-1 == GetFileAttributes(m_strLogPath.c_str()))
		CreateDirectory(m_strLogPath.c_str(), NULL);
}

void Bass::Logger::_Process()
{
	while (true == m_IsRunning)
	{
		if (true == m_queueLog.Empty())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(LOG_DELAY_MS));
			continue;
		}

		time_t currTime = time(nullptr);
		std::string strSaveFileName = m_strLogPath + "\\" + _GetDateString(currTime) + "-" + m_strLogFileName;

		std::ofstream fsLog(strSaveFileName.c_str(), std::ios::app);

		SLogData* pData;

		while (true == m_queueLog.Pop(pData))
		{
			if (nullptr == pData)
				continue;

			std::string strBuffer = std::string(_GetLogLevelString(pData->level)) + " [" + _GetDateTimeString(pData->logTime) + "] " + pData->strLog;
			fsLog << strBuffer << std::endl;

			if (true == m_isShowConsole)
				std::cout << strBuffer << std::endl;

			m_LogPool.Push(pData);
		}

		fsLog.close();
	}
}
