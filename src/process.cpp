#include "process.h"
#include <tlhelp32.h>
#include <iostream>
Process::Process(){
	getPid("elementclient.exe");
}

Process::~Process(){
}
void Process::getPid(char* Name){
	PROCESSENTRY32 pEntry;
	HANDLE pHandle;
	DWORD pid;
	pHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pEntry.dwSize = sizeof(pEntry);
	pid = 0;
	bool loop = Process32First(pHandle, &pEntry);
	while (loop){
		char* pname = pEntry.szExeFile;
		if (pname == Name){
			pid = pEntry.th32ProcessID;
			CloseHandle(pHandle);
		}
		loop = Process32Next(pHandle, &pEntry);
	}
}
Process::printPid()
{
	std::cout<<pid;
}
