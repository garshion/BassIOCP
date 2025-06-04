#pragma once
#include <ctime>
#include <functional>
#include <vector>
#include <atomic>
#include "TimeCommon.h"


namespace std
{
	class thread;
}


namespace Bass
{

	constexpr long long SEC_NANO_VAL = 10000000;


	class TimerData
	{
	private:
		std::tm	m_TimeData;
		ETimerType m_eTimerType = ETimerType::NONE;

		int m_nSetCount = 0;
		int m_nCurrentCount = 0;

		std::function<void()> m_fnTimer = nullptr;
		bool m_isExpired = false;

	public:
		TimerData();
		~TimerData();

		void RegisterFunc(const std::function<void()>& func);

		void SetAlarmData(const ETimerType& type, const int& year, const int& month, const int& day, const int& hour, const int& min, const int& sec);

		void SetAlarmType(const ETimerType& type);
		void SetYear(const int& year);
		void SetMonth(const int& month);
		void SetDay(const int& day);
		void SetDayOfWeek(const EDayOfWeek& day);
		void SetHour(const int& hour);
		void SetMin(const int& min);
		void SetSec(const int& sec);

		void Update(const std::tm& time);	// on Second

		const bool& IsExpired() const;
	private:
		void _SendAlarm();

		void _CheckEvery(const std::tm& time);
		void _CheckEach(const std::tm& time);
		void _CheckOnce(const std::tm& time);
	};

	class TimerImpl
	{
	private:
		std::vector<TimerData*> m_vecAlarmData;
		std::atomic_bool m_IsStarted = false;
		std::thread* m_pThread = nullptr;


	public:
		TimerImpl();
		~TimerImpl();
		void Start();

		bool AddAlarm(const ETimerType& type, const std::tm& time, std::function<void()> fn);

	private:
		void _Process();


	};



}


