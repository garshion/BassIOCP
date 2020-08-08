#include "Console.h"
#include <Windows.h>
#include <string>

void Bass::Console::ChangeConsoleColor(const EConsoleColor& textColor, const EConsoleColor& backColor)
{
	WORD color = (WORD)textColor + (WORD)backColor;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Bass::Console::SetTitle(const char* strTitle)
{
	if (nullptr == strTitle)
		return;

	if (0 == strlen(strTitle))
		return;

	std::string strCommand("TITLE ");
	strCommand.append(strTitle);
	system(strCommand.c_str());
}
