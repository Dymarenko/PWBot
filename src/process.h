#include <windows.h>
class Process
{
public:
	printPid();
	Process();
	~Process();
private:
	DWORD pid;
	void getPid(char* Name);
};
