#pragma once
#include <chrono>

namespace Bass
{
	class StopWatchImpl
	{
	public:
		StopWatchImpl();
		~StopWatchImpl();

		bool Start();
		bool Stop();
		void Reset();

		double GetSeconds() const;
		long long GetMilliseconds() const;
		long long GetNanoseconds() const;

	private:
		std::chrono::system_clock::time_point m_StartTime;
		std::chrono::system_clock::time_point m_EndTime;

		bool m_setStart = false;
		bool m_setEnd = false;

	};

}