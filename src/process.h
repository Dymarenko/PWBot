#ifndef PROCESS_H
#define PROCESS_H
class Process
{
public:
	void printPid();
	Process();
	int readMem(int addr);
private:
	int pid;
	void getPid(char* Name);
};
#endif