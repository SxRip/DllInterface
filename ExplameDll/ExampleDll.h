#define DLLEXPORT extern "C" __declspec(dllexport)

#include <Windows.h>
#include <string>
#include <TlHelp32.h>

DLLEXPORT bool KillProcess(const std::string& processName);