#pragma once
#include <string>
#include <variant>

namespace std
{
	using u8string = std::string;	// UTF-8
}

namespace Bass
{
	class StringUtil
	{
		std::string ToLower(const std::string& str);
		std::u8string ToLower(const std::u8string& str);
		std::wstring ToLower(const std::wstring& str);

		std::string ToUpper(const std::string& str);
		std::u8string ToUpper(const std::u8string& str);
		std::wstring ToUpper(const std::wstring& str);

		std::string ToString(const std::wstring& str);
		std::string ToString(const std::u8string& str);

		std::u8string ToUTF8(const std::string& str);
		std::u8string ToUTF8(const std::wstring& str);

	};

}