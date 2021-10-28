#pragma once
#include "Singleton.h"
#include <cstdint>
#include <ctime>

namespace Bass
{
	/// <summary>
	/// 항상 현재 시간을 측정하는 클래스
	/// </summary>
	class Clock : public Singleton<Clock>
	{
	public:
		time_t GetTime();		// milli sec
		int64_t GetTickNS();	// nano sec
		int64_t GetTick();		// milli sec
	};

}
