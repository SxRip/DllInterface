#include <iostream>
#include "Module\\Module.hpp"

namespace DLLAPI
{
	typedef bool (*KillProcess)(const std::string&);
	typedef NTSTATUS(*NtTestAlert)();
}

void SafeCloseHandle(HANDLE& handle)
{
	if (handle != nullptr)
	{
		CloseHandle(handle);

		handle = nullptr;
	}
}

int main()
{
	DLL modules;

	//Random function from ntdll for test.
	DLLAPI::NtTestAlert pfnNtTestAlert =
		modules.get_func<DLLAPI::NtTestAlert>("NtTestAlert", "ntdll.dll");

	int result = 1337;
	if (pfnNtTestAlert)
	{
		std::cout << "[NtTestAlert] Function is loaded!" << std::endl;
		result = pfnNtTestAlert();

		std::cout << "[NtTestAlert] Tested!\n" << std::endl;
	}

	//Load our explame dll for test the function.
	if (!modules.push_back("ExplameDll.dll"))
	{
		std::cout << "Can't load the dll" << std::endl;
		return -1;
	}

	//Selecting the function from the dll without specifying a dll name
	//because we selected it before.
	DLLAPI::KillProcess pfnKillProcess =
		modules.get_func<DLLAPI::KillProcess>("KillProcess");

	if (pfnKillProcess)
	{
		std::cout << "[KillProcess] Function is loaded!" << std::endl;

		char cWindowSys32Path[MAX_PATH]{};
		if (!GetSystemDirectory(cWindowSys32Path, MAX_PATH))
			return -2;

		std::string sWindowSys32Path = cWindowSys32Path;
		sWindowSys32Path += "\\notepad.exe";

		STARTUPINFO startInfo{ sizeof(startInfo) };
		PROCESS_INFORMATION PI;

		bool bCreated = CreateProcess(sWindowSys32Path.c_str(), nullptr,
			nullptr, nullptr, false, false, nullptr, nullptr, &startInfo, &PI);

		if (bCreated)
		{
			Sleep(1000);
			if (!pfnKillProcess("notepad.exe"))
				return -3;

			std::cout << "[KillProcess] Killed!\n" << std::endl;
		}

		SafeCloseHandle(PI.hProcess);
		SafeCloseHandle(PI.hThread);
	}

	std::cout << "Test completed successfully." << std::endl;
	return 0;
}