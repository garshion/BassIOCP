#pragma once

namespace Bass
{
	constexpr int DAY_PER_SECONDS = 86400;
	constexpr int HOUR_PER_SECONDS = 3600;
	constexpr int MINUTE_PER_SECONDS = 60;


	enum class ETimerType : int
	{
		NONE = 0,
		
		EVERY_SECOND,		// 1초마다 
		EVERY_MINUTE,		// 1분마다
		EVERY_HOUR,			// 1시마다

		EACH_SECOND,		// 1분에 1번 지정 초에
		EACH_MINUTE,		// 1시간에 1번 지정 분,초에 
		EACH_HOUR,			// 하루에 1번 지정 시,분,초에
		EACH_DAY,			// 한달에 1번 지정 일,시,분,초에
		EACH_DAY_OF_WEEK,	// 1주일에 1번 지정 요일,시,분,초에

		ONCE,				// 년,월,일,시,분,초에 딱 한번.

		MAX,
	};

	enum class EDayOfWeek : int
	{
		Sunday = 0,			// 일
		Monday,				// 월
		Tuesday,			// 화
		Wednesday,			// 수
		Thursday,			// 목
		Friday,				// 금
		Saturday,			// 토
	};




}