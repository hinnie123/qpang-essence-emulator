#ifndef STRING_CONVERTER_HPP
#define STRING_CONVERTER_HPP

#include <iostream>
#include <string>
#include <algorithm>

class StringConverter {
public:
	static std::string Utf16ToUtf8(std::u16string string);
	static std::u16string Utf8ToUtf16(std::string string);
	static std::wstring StringToWString(std::string string);
	static std::string WStringToString(std::wstring string);
	static const wchar_t* StringToWChar(std::string string, const size_t size = 0);
	static std::string WcharToString(wchar_t* wideString, const size_t size);
	static std::string ToLowerCase(std::string string);
	static std::u16string ToLowerCase(std::u16string string);
};

#endif // !STRING_CONVERTER_HPP
