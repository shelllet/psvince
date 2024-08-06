#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <TlHelp32.h>
#include <versionhelpers.h>
#include <psapi.h>

BOOL WINAPI EnumProcs(char* procname);


BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	UNREFERENCED_PARAMETER(hModule);
	UNREFERENCED_PARAMETER(ul_reason_for_call);
	UNREFERENCED_PARAMETER(lpReserved);
	return TRUE;
}

int APIENTRY IsModuleLoaded(char* lpModule)
{
	char procName[MAX_PATH] = { 0 };
	strcpy_s(procName, lpModule);
	return EnumProcs(procName);
}


BOOL WINAPI EnumProcs(char* procname)
{
	HANDLE handleToSnapshot;
	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32);
	handleToSnapshot = CreateToolhelp32Snapshot(2, 0);

	bool nRet = false;
	_strlwr_s(procname, strlen(procname) + 1);

	if (Process32First(handleToSnapshot, &procEntry)) {
		do {
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, procEntry.th32ProcessID);

			if (hProcess != NULL)
			{
				char filePath[MAX_PATH] = { 0 };
				if (GetModuleFileNameExA(hProcess, NULL, filePath, MAX_PATH))
				{
					_strlwr_s(filePath, MAX_PATH);

					if (strstr(filePath, procname) != nullptr) {
						nRet = TRUE;
					}
				}

				CloseHandle(hProcess);
			}

			if (nRet)
			{
				break;
			}
		} while (Process32Next(handleToSnapshot, &procEntry));
	}

	CloseHandle(handleToSnapshot);

	return nRet;
}
