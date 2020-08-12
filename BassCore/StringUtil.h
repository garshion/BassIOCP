#pragma once
#include <string>
#include <variant>

namespace Bass
{
	class StringUtil
	{
	public:
		static std::string ToLower(const std::string& str);
		static std::wstring ToLower(const std::wstring& str);

		static std::string ToUpper(const std::string& str);
		static std::wstring ToUpper(const std::wstring& str);

		static std::string ToMBS(const std::wstring& str);
		static std::wstring ToWCS(const std::string& str);

#ifdef _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
		static std::string ToUTF8(const std::string& str);
		static std::string ToUTF8(const std::wstring& str);

		static std::wstring UTF8ToWCS(const std::string& str);
		static std::string UTF8ToMBS(const std::string& str);
#endif
	};

}