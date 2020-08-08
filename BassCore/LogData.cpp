#include "LogData.h"
#include "StringUtil.h"
//#include <chrono>

Bass::LogData::LogData()
{
}

Bass::LogData::LogData(const ELogLevel& logLevel, const std::wstring& strLog)
{
	SetData(logLevel, strLog);
}

Bass::LogData::LogData(const ELogLevel& logLevel, const std::string& strLog)
{
	SetData(logLevel, StringUtil::ToWCS(strLog));
}


void Bass::LogData::SetData(const ELogLevel& logLevel, const std::wstring& strLog)
{
	LogLevel = logLevel;
	LogString.assign(strLog.begin(), strLog.end());
	SetTime();
}

void Bass::LogData::SetData(const ELogLevel& logLevel, const std::string& strLog)
{
	SetData(logLevel, StringUtil::ToWCS(strLog));
}

void Bass::LogData::SetTime()
{
	LogTime = std::chrono::system_clock::now();
}

std::wstring Bass::LogData::ToString()
{
	std::tm timeData;
	time_t logTime = std::chrono::system_clock::to_time_t(LogTime);
	if (0 != localtime_s(&timeData, &logTime))
		return L"Time Error!!";

	wchar_t strTemp[50] = { 0, };
	size_t nOffset = wcsftime(strTemp, _countof(strTemp), L"[%Y-%m-%d %H:%M:%S", &timeData);

	// 이제  ms 처리...
	int nMS = (int)(std::chrono::duration_cast<std::chrono::milliseconds>(LogTime.time_since_epoch()).count() % 1000);
	swprintf_s(strTemp + nOffset, 50 - nOffset, L".%03d]", nMS);

	std::wstring strRet(strTemp);
	strRet.append(L" ");
	strRet.append(_GetLogTypeString(LogLevel));
	strRet.append(L" ");
	strRet.append(LogString);

	return strRet;
}

const wchar_t* Bass::LogData::_GetLogTypeString(const ELogLevel& level) const
{
	switch (level)
	{
	case ELogLevel::Info: return L"[INFO]";
	case ELogLevel::Warning: return L"[WARN]";
	case ELogLevel::Error: return L"[ERROR]";
	case ELogLevel::Debug: return L"[DEBUG]";
	case ELogLevel::Console: return L"";
	case ELogLevel::System: return L"[SYSTEM]";
	default:
		break;
	}
	return L"[UNKNOWN]";
}
