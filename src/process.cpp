#include "process.h"
#include <wine/windows/windows.h>
#include <wine/windows/tlhelp32.h>
Process::Process(){
	pid = getPid("elementclient.exe");
}
int Process::getPid(char* Name){
	PROCESSENTRY32 ProcessEntry;
	HANDLE pHandle;
	pHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	ProcessEntry.dwSize = sizeof(ProcessEntry);
	pid=0;
	bool loop=Process32First(pHandle, &ProcessEntry);
	while (loop)
	{
		char* nm=ProcessEntry.szExeFile;
		if (nm==Name)
		{
		pid = ProcessEntry.th32ProcessID;
		CloseHandle(pHandle);
		break;
		}
		loop=Process32Next(pHandle, &ProcessEntry);
	}
}
int Process::readMem(int addr)
{
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS,false,pid);
	int value;
	ReadProcessMemory(hProc,(void*)addr,&value,4,0);
	CloseHandle(hProc);
	return value;
}
#include <iostream>
void Process::printPid(){
	std::cout << pid << "\n";
}
