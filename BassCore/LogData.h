#pragma once
#include <string>
#include <chrono>

namespace Bass
{
	enum class ELogLevel : int
	{
		None = 0,
		Info,			// �Ϲ� �α� (���� ȸ��)
		Warning,		// ��� �α� (�����)
		Error,			// ���� �α� (������)
		Debug,			// ����� �α� (�ϴû�)
		Console,		// �ֿܼ��� ������ �α� (���� ȸ��)
		System,			// ���� �ý��� ���� �α� (���)
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