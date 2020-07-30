#pragma once
#include "Singleton.h"


namespace Bass
{
	enum class ELogLevel : int
	{
		None = 0,
		Info,
		Warning,
		Error,
		Debug,
		Console,
		Max,
	};



	class LogManager : public Singleton<LogManager>
	{
	public:
		LogManager();
		~LogManager();





	};

}