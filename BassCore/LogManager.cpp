#include "LogManager.h"
#include "LogManagerImpl.hxx"
#include "BassCommon.h"
#include <Windows.h>
#include <cstdio>

Bass::LogManager::LogManager()
{
	m_pLogManager = new LogManagerImpl();
}

Bass::LogManager::~LogManager()
{
	Stop();
	SafeDelete(m_pLogManager);
}

void Bass::LogManager::SetPath(const std::wstring& strDir, const std::wstring& strFileName)
{
	if (nullptr != m_pLogManager)
		m_pLogManager->SetPath(strDir, strFileName);
}

void Bass::LogManager::SetLogPath(const std::wstring& strLogPath)
{
	if (nullptr != m_pLogManager)
		m_pLogManager->SetLogPath(strLogPath);
}

void Bass::LogManager::SetLogFileName(const std::wstring& strLogFileName)
{
	if (nullptr != m_pLogManager)
		m_pLogManager->SetLogFileName(strLogFileName);
}

void Bass::LogManager::SetLogWriteTickDelayMS(const int& nLogTickMS)
{
	if (nullptr != m_pLogManager)
		m_pLogManager->SetLogWriteTickDelayMS(nLogTickMS);
}

void Bass::LogManager::SetLogFileMaxSize(const size_t& nLogFileMaxSize)
{
	if (nullptr != m_pLogManager)
		m_pLogManager->SetLogFileMaxSize(nLogFileMaxSize);
}

void Bass::LogManager::Start()
{
	if (nullptr != m_pLogManager)
		m_pLogManager->Start();
}

void Bass::LogManager::Stop()
{
	if (nullptr != m_pLogManager)
		m_pLogManager->Stop();
}

void Bass::LogManager::Info(const wchar_t* format, ...)
{
	if (nullptr == m_pLogManager)
		return;

	wchar_t pBuffer[VARIABLE_FORMAT_BUFFER_SIZE] = { 0, };
	va_list args;
	va_start(args, format);
	_vsnwprintf_s(pBuffer, VARIABLE_FORMAT_BUFFER_SIZE, VARIABLE_FORMAT_BUFFER_SIZE - 1, format, args);
	va_end(args);

	m_pLogManager->Log(pBuffer, ELogLevel::Info);
}

void Bass::LogManager::Warning(const wchar_t* format, ...)
{
	if (nullptr == m_pLogManager)
		return;

	wchar_t pBuffer[VARIABLE_FORMAT_BUFFER_SIZE] = { 0, };
	va_list args;
	va_start(args, format);
	_vsnwprintf_s(pBuffer, VARIABLE_FORMAT_BUFFER_SIZE, VARIABLE_FORMAT_BUFFER_SIZE - 1, format, args);
	va_end(args);

	m_pLogManager->Log(pBuffer, ELogLevel::Warning);
}

void Bass::LogManager::Error(const wchar_t* format, ...)
{
	if (nullptr == m_pLogManager)
		return;

	wchar_t pBuffer[VARIABLE_FORMAT_BUFFER_SIZE] = { 0, };
	va_list args;
	va_start(args, format);
	_vsnwprintf_s(pBuffer, VARIABLE_FORMAT_BUFFER_SIZE, VARIABLE_FORMAT_BUFFER_SIZE - 1, format, args);
	va_end(args);

	m_pLogManager->Log(pBuffer, ELogLevel::Error);
}

void Bass::LogManager::Debug(const wchar_t* format, ...)
{
#ifdef _DEBUG
	if (nullptr == m_pLogManager)
		return;

	wchar_t pBuffer[VARIABLE_FORMAT_BUFFER_SIZE] = { 0, };
	va_list args;
	va_start(args, format);
	_vsnwprintf_s(pBuffer, VARIABLE_FORMAT_BUFFER_SIZE, VARIABLE_FORMAT_BUFFER_SIZE - 1, format, args);
	va_end(args);

	m_pLogManager->Log(pBuffer, ELogLevel::Debug);
#endif
}

void Bass::LogManager::Console(const wchar_t* format, ...)
{
	if (nullptr == m_pLogManager)
		return;

	wchar_t pBuffer[VARIABLE_FORMAT_BUFFER_SIZE] = { 0, };
	va_list args;
	va_start(args, format);
	_vsnwprintf_s(pBuffer, VARIABLE_FORMAT_BUFFER_SIZE, VARIABLE_FORMAT_BUFFER_SIZE - 1, format, args);
	va_end(args);

	m_pLogManager->Log(pBuffer, ELogLevel::Console);
}

void Bass::LogManager::System(const wchar_t* format, ...)
{
	if (nullptr == m_pLogManager)
		return;

	wchar_t pBuffer[VARIABLE_FORMAT_BUFFER_SIZE] = { 0, };
	va_list args;
	va_start(args, format);
	_vsnwprintf_s(pBuffer, VARIABLE_FORMAT_BUFFER_SIZE, VARIABLE_FORMAT_BUFFER_SIZE - 1, format, args);
	va_end(args);

	m_pLogManager->Log(pBuffer, ELogLevel::System);
}
