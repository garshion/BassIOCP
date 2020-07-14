#pragma once
#include <chrono>

typedef std::chrono::system_clock::time_point timepoint_t;
typedef std::chrono::duration<double> sec_t;
typedef std::chrono::milliseconds ms_t;
typedef std::chrono::nanoseconds ns_t;



#define CurrentTime() std::chrono::system_clock::now()


#define DAY_PER_SECONDS 86400
#define HOUR_PER_SECONDS 3600
#define MINUTE_PER_SECONDS 60



