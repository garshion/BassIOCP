#pragma once
#include "Singleton.h"
#include <cstdint>
#include <ctime>

namespace Bass
{
	/// <summary>
	/// �׻� ���� �ð��� �����ϴ� Ŭ����
	/// </summary>
	class Clock : public Singleton<Clock>
	{
	public:
		time_t GetTime();		// milli sec
		int64_t GetTickNS();	// nano sec
		int64_t GetTick();		// milli sec
	};

}
