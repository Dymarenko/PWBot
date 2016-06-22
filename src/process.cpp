#include "process.h"
#include "addr.h"

Process::Process(){
	getPid("elimentclient.exe");
}
void Process::getPid(char* Name){
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
DWORD Process::readMem(DWORD addr)
{
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS,false,pid);
	DWORD value;
	ReadProcessMemory(hProc,(void*)addr,&value,4,0);
	CloseHandle(hProc);
	return value;
}
#include <iostream>
void Process::printPid(){
	std::cout << pid << "\n";
}
DWORD Process::jumpToPersStruct(){
	DWORD buff;
	buff = readMem(BaseAddr);
	buff = readMem(buff + GameAddr);
	buff = readMem(buff + PersStruct);
	return buff;
}