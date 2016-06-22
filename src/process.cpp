#include "process.h"
#include <wine/windows/windows.h>
#include <wine/windows/tlhelp32.h>
Process::Process(){
	pid = getPid();
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
int Process::readMem_32(int addr)
{
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS,false,pid);
}
#include <iostream>
void Process::printPid(){
	std::cout << pid << "\n";
}
