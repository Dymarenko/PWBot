#include "process.h"
#include "addr.h"
#include <Windows.h>
#include <cstring>
#include <iostream>

Process::Process(){
	getPid("elementclient.exe");
}
void Process::getPid(char* Name){
	PROCESSENTRY32 ProcessEntry;
	HANDLE pHandle;
	pHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	ProcessEntry.dwSize = sizeof(ProcessEntry);
	pid=-1;
	bool loop=Process32First(pHandle, &ProcessEntry);
	while (loop)
	{
		char* nm=ProcessEntry.szExeFile;
		if (strcmp((char*)nm, Name) == 0)
		{
			pid = ProcessEntry.th32ProcessID;
			CloseHandle(pHandle);
			break;
		}
		loop=Process32Next(pHandle, &ProcessEntry);
	}
}
DWORD Process::readMem(DWORD addr){
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    DWORD value;
    ReadProcessMemory(hProcess, (void*)addr, &value, sizeof(value), 0);
    CloseHandle(hProcess);
    return value;
}
float Process::readMem_f(DWORD addr){
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    float value;
    ReadProcessMemory(hProcess, (void*)addr, &value, sizeof(value), 0);
    CloseHandle(hProcess);
    return value;
}
wchar_t* Process::readMem_8s(DWORD addr)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	wchar_t value[8];
	ReadProcessMemory(hProcess, (void*)addr, &value, sizeof(value), 0);
	CloseHandle(hProcess);
	return value;
}
DWORD Process::jumpToPersStruct(){
	return readMem(readMem(GameAddr) + PersStruct);
}
DWORD Process::givepid(){
	return pid;
}
