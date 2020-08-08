#pragma once
#include <string>
#include <chrono>

namespace Bass
{
	enum class ELogLevel : int
	{
		None = 0,
		Info,			// 일반 로그 (밝은 회색)
		Warning,		// 경고성 로그 (노란색)
		Error,			// 오류 로그 (빨간색)
		Debug,			// 디버그 로그 (하늘색)
		Console,		// 콘솔에만 찍히는 로그 (밝은 회색)
		System,			// 서버 시스템 관련 로그 (녹색)
		Max,
	};

	/*
		Log Format
		[YYYY-MM-DD HH:mm:ss.xxx] [TYPE] LogMessage...
	*/


	class LogData
	{
	public:
		LogData();
		LogData(const ELogLevel& logLevel, const std::wstring& strLog);
		LogData(const ELogLevel& logLevel, const std::string& strLog);

		~LogData() = default;

		void SetData(const ELogLevel& logLevel, const std::wstring& strLog);
		void SetData(const ELogLevel& logLevel, const std::string& strLog);
		void SetTime();

		std::wstring ToString();

	private:
		const wchar_t* _GetLogTypeString(const ELogLevel& level) const;

	public:
		ELogLevel	LogLevel = ELogLevel::None;
		std::chrono::system_clock::time_point LogTime;
		std::wstring LogString = L"";
	};

}