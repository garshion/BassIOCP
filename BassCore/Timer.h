#pragma once
#include <functional>
#include "Singleton.h"
#include "TimeCommon.h"

namespace Bass
{
	class TimerImpl;
	class Timer : public Singleton<Timer>
	{
	public:
		Timer();
		virtual ~Timer();

		void Start();
		bool AddAlarm(const ETimerType& type, const std::tm& time, std::function<void()> fn);
	private:
		TimerImpl* m_pImpl = nullptr;
	};
}

