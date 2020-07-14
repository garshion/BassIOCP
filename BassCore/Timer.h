#pragma once
#include "TimeCommon.h"
#include <thread>
#include <vector>
#include <unordered_map>
#include <mutex>

namespace Bass
{
	typedef void(*OnTimerFunc)(void);	// Event 받을 함수 포인터. void Func(void) 형태만 받음.
	typedef std::vector<OnTimerFunc> vecOnTimer_t;

	enum ETimerType
	{
		TIMER_TYPE_SECOND,
		TIMER_TYPE_MINUTE,
		TIMER_TYPE_HOUR,
		TIMER_TYPE_DAY,
	};

	class Timer
	{
	public:

		Timer(bool bUseSystemClock = true);
		~Timer();

		bool AddTimerEvent(OnTimerFunc pEvent, ETimerType type);
		void RemoveTimerEvent(OnTimerFunc pEvent);

	private:

		void _Process();

		void _OnEvent(ETimerType type);

		void _OnSecond();
		void _OnMinute();
		void _OnHour();
		void _OnDay();

		void _Initialize();
		void _Release();

	private:
		bool m_bUseSystemClock;
		bool m_IsRunning = false;

		timepoint_t m_BaseTime;
		int m_nBaseTimeCount = 0;



		vecOnTimer_t m_vecSec;
		vecOnTimer_t m_vecMin;
		vecOnTimer_t m_vecHour;
		vecOnTimer_t m_vecDay;

		std::unordered_map<OnTimerFunc, ETimerType> m_mapTimerEvent;


		std::thread* m_pThread = nullptr;
		std::mutex m_Lock;
	};

}