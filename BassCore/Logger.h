#pragma once
//#include <string>
//#include <chrono>
//#include <atomic>
//#include "MTQueue.h"
//#include "MemoryPool.h"
//
//#define DEFAULT_LOG_PATH "./Log/"
//#define DEFAULT_LOG_FILENAME "Log.txt"
//#define DEFAULT_LOG_POOL_SIZE 2000
//#define LOG_DELAY_MS 50
//namespace Bass
//{
//	enum ELogLevel
//	{
//		LOG_LEVEL_INFO = 1,
//		LOG_LEVEL_WARN,
//		LOG_LEVEL_ERROR,
//		LOG_LEVEL_DEBUG,
//	};
//
//	struct SLogData
//	{
//		ELogLevel level;
//		time_t logTime;
//		std::string strLog;
//	};
//
//
//	class Logger
//	{
//	public:
//		Logger();
//		~Logger();
//
//		void Start();
//		void Stop();
//
//		void SetLogPath(const std::string& strPath = DEFAULT_LOG_PATH);
//		void SetLogFileName(const std::string& strFileName = DEFAULT_LOG_FILENAME);
//
//		void Info(const char* format, ...);
//		void Warning(const char* format, ...);
//		void Error(const char* format, ...);
//		void Debug(const char* format, ...);
//
//		void Console(const char* format, ...);				// 콘솔에만 찍는 로그
//
//		void Log(const std::string& log, ELogLevel level);
//
//
//
//	private:
//
//		const char* _GetLogLevelString(const ELogLevel& level) const;
//		std::string _GetDateTimeString(const time_t& timeValue) const;
//		std::string _GetDateString(const time_t& timeValue) const;
//
//		void _CheckAndMakeFolder();
//		void _Process();
//
//	private:
//		std::string m_strLogPath;
//		std::string m_strLogFileName;
//
//		MTQueue<SLogData*> m_queueLog;
//		MemoryPool<SLogData> m_LogPool;
//
//		std::thread* m_pThread = nullptr;
//
//		std::atomic_bool m_IsRunning = false;
//		std::atomic_bool m_isShowConsole = true;
//
//	};
//
//}