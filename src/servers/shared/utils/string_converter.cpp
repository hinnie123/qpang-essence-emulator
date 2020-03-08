#include "string_converter.hpp"
#include <boost/locale/encoding_utf.hpp>

using boost::locale::conv::utf_to_utf;
std::string StringConverter::Utf16ToUtf8(std::u16string string)
{
	return utf_to_utf<char, char16_t>(string.c_str());
}

std::u16string StringConverter::Utf8ToUtf16(std::string string)
{
	return utf_to_utf<char16_t, char>(string.c_str());
}

std::wstring StringConverter::StringToWString(std::string string)
{
	return utf_to_utf<wchar_t>(string.c_str(), string.c_str() + string.size());
}

std::string StringConverter::WStringToString(std::wstring string)
{
	return utf_to_utf<char>(string.c_str(), string.c_str() + string.size());
}

const wchar_t* StringConverter::StringToWChar(std::string string, size_t size)
{
	std::wstring wstring = StringToWString(string);
	return wstring.data();
}

std::string StringConverter::WcharToString(wchar_t* wideString, const size_t size)
{
	auto string = std::wstring(wideString);
	return WStringToString(string);
}

std::string StringConverter::ToLowerCase(std::string string)
{
	std::string someString(string);
	std::transform(someString.begin(), someString.end(), someString.begin(), ::tolower);
	return someString;
}

std::u16string StringConverter::ToLowerCase(std::u16string string)
{
	std::u16string someString(string);
	std::transform(someString.begin(), someString.end(), someString.begin(), ::tolower);
	return someString;
}
