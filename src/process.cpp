#include "process.h"
#include <windows.h>
#include <tlhelp32.h>

Process::Process(){
	pid = getPid();
}
int Process::getPid(){
	
}