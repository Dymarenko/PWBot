#include "process.h"
#include <tlhelp32.h>

Process::Process(){
	pid = getPid();
}
int Process::getPid(char* Name){
	PROCESSENTRY32 ProcessEntry;
	HANDLE pHandle;
	DWORD pid;
	pHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	ProcessEntry.dwSize = sizeof(ProcessEntry);
	pid=0;
	bool loop=Process32First(pHandle, &ProcessEntry);
	while (loop)
	{
		AnsiString nm=ProcessEntry.szExeFile;
		if (nm==Name)
		{
		pid = ProcessEntry.th32ProcessID;
		CloseHandle(pHandle);
		break;
		}
		loop=Process32Next(pHandle, &ProcessEntry);
	}
}
