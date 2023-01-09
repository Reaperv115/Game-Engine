#include "trpch.h"
#include "ErrorLogger.h"


void ErrorLogger::Log(std::string message)
{
	std::string error_message = "Error: " + message;
	MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::string message)
{
	std::wstring error_message = L"Error: " + StringConverter::StringtoWideString(message) +
		L"\n";
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::wstring message)
{
	std::wstring errorMessage = L"Error: " + message + L"\n";
	MessageBoxW(NULL, errorMessage.c_str(), L"Error", MB_ICONERROR);
}
