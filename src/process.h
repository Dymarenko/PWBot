class Process
{
public:
	void printPid();
	Process();
private:
	int pid;
	void getPid(char* Name);
	int readMem_32(int addr);
};