#include "injector.h"
#include <iostream>
#include <string>
injector::injector(){
}
void injector::setFuncAlloc(){
    HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    DWORD* pfunc = (DWORD*)VirtualAllocEx(hProcess, NULL, 127, MEM_COMMIT, PAGE_READWRITE);
    if (pfunc == NULL) {std::cout<<"Error memory alloc!\n";}
    pFunc = pfunc;
    pParams = pfunc + 64;
    CloseHandle(hProcess);
}
byte injector::injectAndExecute(void* func, void* param){
	if (pid == 0) { std::cout << "Error!\n"; return 0; }
    HANDLE hProcThread;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if (!hProcess) return 0;

    WriteProcessMemory(hProcess, pFunc, func, 250, NULL);
    WriteProcessMemory(hProcess, pParams, param, 250, NULL);

    hProcThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)pFunc, pParams, NULL, NULL);
    if(hProcThread==INVALID_HANDLE_VALUE) return 0;
	std::cout << "Eurika!\n";
	
    WaitForSingleObject(hProcThread, INFINITE);
    CloseHandle(hProcThread);
    CloseHandle(hProcess);
    return 1;
}
void Target_Thread(DWORD* WID){
    DWORD Id = *WID;
	__asm
	{
		MOV ESI, Id
		MOV EBP, 0x0071AAE0
		MOV EAX, DWORD PTR DS : [0xC7CA6C]
		PUSH ESI
		MOV ECX, DWORD PTR DS:[EAX+0x20]
		ADD ECX, 0x0F4
		CALL EBP
	}
}
void injector::targetmob(DWORD wid){
    injectAndExecute(&Target_Thread, &wid);
}
