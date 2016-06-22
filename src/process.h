#include <windows.h>
#include <tlhelp32.h>
#ifndef PROCESS_H
#define PROCESS_H
class Process
{
public:
	void printPid();
	Process();
	DWORD readMem(DWORD addr);
private:
	DWORD pid;
	void getPid(char* Name);
	DWORD jumpToPersStruct();
};
#endif