#include "pch.h"
#include "ExampleDll.h"

void SafeCloseHanle(HANDLE& handle)
{
	if (handle != nullptr)
	{
		CloseHandle(handle);

		handle = nullptr;
	}
}

DLLEXPORT bool KillProcess(const std::string& processName)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (!hSnap)
		return false;

	PROCESSENTRY32 pe{ sizeof(pe) };

	while (Process32Next(hSnap, &pe))
		if (processName == pe.szExeFile)
		{
			SafeCloseHanle(hSnap);

			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pe.th32ProcessID);

			if (hProcess)
				if (TerminateProcess(hProcess, 0))
				{
					SafeCloseHanle(hProcess);
					return true;
				}
		}

	SafeCloseHanle(hSnap);
	return false;
}