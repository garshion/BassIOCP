#pragma once

namespace Bass
{
	enum class EConsoleColor : int
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15,

		Background_Black = 0,
		Background_Blue = 1 * 16,
		Background_Green = 2 * 16,
		Background_Cyan = 3 * 16,
		Background_Red = 4 * 16,
		Background_Magenta = 5 * 16,
		Background_Brown = 6 * 16,
		Background_LightGray = 7 * 16,
		Background_DarkGray = 8 * 16,
		Background_LightBlue = 9 * 16,
		Background_LightGreen = 10 * 16,
		Background_LightCyan = 11 * 16,
		Background_LightRed = 12 * 16,
		Background_LightMagenta = 13 * 16,
		Background_Yellow = 14 * 16,
		Background_White = 15 * 16,
 	};

	class Console
	{
	public:
		static void ChangeConsoleColor(const EConsoleColor& textColor = EConsoleColor::LightGray, const EConsoleColor& backColor = EConsoleColor::Background_Black);
		static void SetTitle(const char* strTitle);
	};

}