#include "StringUtil.h"
#include "BassCommon.h"
#include <algorithm>
#include <locale>
#include <codecvt>

std::string Bass::StringUtil::ToLower(const std::string& str)
{
	std::string strRet(str);
	std::transform(strRet.begin(), strRet.end(), strRet.begin(), [](char c) {return (char)std::tolower(c); });
	return strRet;
}

std::wstring Bass::StringUtil::ToLower(const std::wstring& str)
{
	std::wstring strRet(str);
	std::transform(strRet.begin(), strRet.end(), strRet.begin(), [](char c) {return (wchar_t)std::tolower(c); });
	return strRet;
}

std::string Bass::StringUtil::ToUpper(const std::string& str)
{
	std::string strRet(str);
	std::transform(strRet.begin(), strRet.end(), strRet.begin(), [](char c) {return (char)std::toupper(c); });
	return strRet;
}

std::wstring Bass::StringUtil::ToUpper(const std::wstring& str)
{
	std::wstring strRet(str);
	std::transform(strRet.begin(), strRet.end(), strRet.begin(), [](char c) {return (wchar_t)std::toupper(c); });
	return strRet;
}

std::string Bass::StringUtil::ToMBS(const std::wstring& str)
{
	setlocale(LC_ALL, "");
	std::string strRet = "";
	size_t wstrSize = (str.length() * sizeof(wchar_t)) + 1;
	char* pTemp = new char[wstrSize] { 0, };
	size_t nConverted = 0;

	auto err = wcstombs_s(&nConverted, pTemp, wstrSize, str.c_str(), _TRUNCATE);
	if (err == 0)
		strRet.append(pTemp);

	SafeDeleteArray(pTemp);
	return strRet;
}

std::wstring Bass::StringUtil::ToWCS(const std::string& str)
{
	setlocale(LC_ALL, "");
	std::wstring strRet = L"";
	size_t strSize = str.length() + 1;
	wchar_t* pTemp = new wchar_t[strSize] { 0, };
	size_t nConverted = 0;

	if (0 == mbstowcs_s(&nConverted, pTemp, strSize, str.c_str(), _TRUNCATE))
		strRet.append(pTemp);

	SafeDeleteArray(pTemp);
	return strRet;
}

std::string Bass::StringUtil::ToUTF8(const std::string& str)
{
	return ToUTF8(ToWCS(str));
}

std::string Bass::StringUtil::ToUTF8(const std::wstring& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convertor;
	return convertor.to_bytes(str.c_str());
}

std::wstring Bass::StringUtil::UTF8ToWCS(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convertor;
	return convertor.from_bytes(str.c_str());
}

std::string Bass::StringUtil::UTF8ToMBS(const std::string& str)
{
	return ToMBS(UTF8ToWCS(str));
}
