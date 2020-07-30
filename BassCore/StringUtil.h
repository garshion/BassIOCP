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


		std::string ToString(const std::wstring& str);
		std::wstring ToWString(const std::string& str);


	};

}