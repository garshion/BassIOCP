#pragma once
#include "TimeCommon.h"
#include <thread>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <functional>

#ifdef WORKING

namespace Bass
{
	//typedef void(*OnTimerFunc)(void);	// Event 받을 함수 포인터. void Func(void) 형태만 받음.
	//typedef std::vector<OnTimerFunc> vecOnTimer_t;

	using vecOnTimer_t = std::vector<std::function<void>>;

	//enum class ETimerType : int
	//{
	//	ON_SECOND = 0,
	//	ON_MINUTE,
	//	ON_HOUR,
	//	ON_DAY,
	//};

	class Timer
	{
	public:

		Timer(bool bUseSystemClock = true);
		~Timer();

		bool AddTimerEvent(const std::function<void>& pEvent, const ETimerType& type);
		bool RemoveTimerEvent(const std::function<void>& pEvent);
		//bool AddTimerEvent(OnTimerFunc pEvent, ETimerType type);
		//void RemoveTimerEvent(OnTimerFunc pEvent);

	private:

		void _Process();

		void _OnEvent(const ETimerType& type);

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

		//std::unordered_map<OnTimerFunc, ETimerType> m_mapTimerEvent;
		std::unordered_map<std::function<void>, ETimerType> m_mapTimerEvent;


		std::thread* m_pThread = nullptr;
		std::mutex m_Lock;
	};

}

#endif