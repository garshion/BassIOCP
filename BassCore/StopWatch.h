#pragma once
#include <cstdint>

namespace Bass
{
	class StopWatchImpl;

	/// <summary>
	/// 두 구간의 시간을 측정할 수 있는 클래스
	/// </summary>
	class StopWatch
	{
	public:
		StopWatch();
		~StopWatch();

		bool Start();	// 측정 시작
		bool Stop();	// 측정 종료
		void Reset();	// 초기화

		double GetSeconds() const;			// 두 지점의 차이 (초)
		int64_t GetMilliseconds() const;	// 두 지점의 차이 (밀리초)
		int64_t GetNanoseconds() const;		// 두 지점의 차이 (나노초)

	private:
		StopWatchImpl* m_pImpl = nullptr;

	};

}