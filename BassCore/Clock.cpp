#include "Clock.h"
#include <chrono>

time_t Bass::Clock::GetTime()
{
	return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

int64_t Bass::Clock::GetTickNS()
{
	return std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now()).time_since_epoch().count();;
}

int64_t Bass::Clock::GetTick()
{
	return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();;
}
