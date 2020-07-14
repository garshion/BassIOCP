#pragma once

#include "TimeCommon.h"

namespace Bass
{
	class StopWatch
	{
	public:
		StopWatch();
		~StopWatch();

		bool Start();
		bool Stop();
		void Reset();

		double GetSeconds() const;
		long long GetMilliseconds() const;
		long long GetNanoseconds() const;

	private:
		timepoint_t m_StartTime;
		timepoint_t m_EndTime;

		bool m_setStart = false;
		bool m_setEnd = false;
	};

}