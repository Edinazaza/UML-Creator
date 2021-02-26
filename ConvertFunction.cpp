#include "ConvertFunction.h"

//конвертируем System::string^ в std::string
std::string& Convert_String_to_string(String^ s, std::string& os) 
{
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return os;
}

//конвертируем std::string в System::string^
String^ Convert_string_to_String(std::string& os, String^ s) 
{
	s = gcnew System::String(os.c_str());
	return s;
}

//конвертируем System::string^ в std::string
std::string& Convert_String_to_string(String^ s) 
{
	std::string os;
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return os;
}

//конвертируем std::string в System::string^
String^ Convert_string_to_String(std::string& os) 
{
	System::String^ s = gcnew System::String(os.c_str());
	return s;
}

//конвертируем char в System::string^
System::String^ Convert_char_to_String(char ch) 
{
	char* chr = new char();
	chr[0] = ch;
	System::String^ str;
	for (int i = 0; chr[i] != '\0'; i++)
		str += wchar_t(ch);
	return str;
}

//конвертируем System::string^ в char*
char* Convert_String_to_char(System::String^ string) 
{
	using namespace System::Runtime::InteropServices;
	return (char*)(void*)Marshal::StringToHGlobalAnsi(string);
}

//конвертируем char* в System::string^
System::String^ Convert_char_to_String(char* ch) 
{
	char* chr = new char();
	chr = ch;
	System::String^ str;
	for (int i = 0; chr[i] != '\0'; i++)
		str += wchar_t(ch[i]);
	return str;
}
