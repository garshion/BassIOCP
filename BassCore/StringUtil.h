#pragma once
#include <string>
#include <variant>


namespace Bass
{
	class StringUtil
	{
		std::string ToLower(const std::string& str);
		std::wstring ToLower(const std::wstring& str);

		std::string ToUpper(const std::string& str);
		std::wstring ToUpper(const std::wstring& str);

		std::string ToMBS(const std::wstring& str);
		std::wstring ToWCS(const std::string& str);

		std::string ToUTF8(const std::string& str);
		std::string ToUTF8(const std::wstring& str);

		std::wstring UTF8ToWCS(const std::string& str);
		std::string UTF8ToMBS(const std::string& str);

	};

}