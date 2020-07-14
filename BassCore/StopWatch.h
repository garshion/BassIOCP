#pragma once
#include <cstdint>

namespace Bass
{
	class StopWatchImpl;
	class StopWatch
	{
	public:
		StopWatch();
		~StopWatch();

		bool Start();
		bool Stop();
		void Reset();

		double GetSeconds() const;
		int64_t GetMilliseconds() const;
		int64_t GetNanoseconds() const;

	private:
		StopWatchImpl* m_pImpl = nullptr;

	};

}