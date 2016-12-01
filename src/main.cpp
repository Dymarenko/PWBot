#include "person.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string char_to_str(char* input) {
	string buff;
	buff.append(input);
	return buff;
}
wchar_t* str_to_wchar(char* input)
{
	wchar_t* output = new wchar_t[strlen(input) + 1];
	for (unsigned int i = 0; i < strlen(input) + 1; i++)
	{
		const char sim_buf = input[i];
		wchar_t out_buf;
		MultiByteToWideChar(1251, 0, &sim_buf, sizeof(sim_buf), &out_buf, sizeof(out_buf));
		output[i] = out_buf;
	}
	return output;
}
vector <DWORD> getPidsVec(char* Name) {
	PROCESSENTRY32 ProcessEntry;
	HANDLE pHandle;
	vector <DWORD> pids;
	pHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	ProcessEntry.dwSize = sizeof(ProcessEntry);
	bool loop = Process32First(pHandle, &ProcessEntry);
	while (loop)
	{
		char* nm = ProcessEntry.szExeFile;
		if (strcmp((char*)nm, Name) == 0)
		{
			pids.push_back(ProcessEntry.th32ProcessID);
		}
		loop = Process32Next(pHandle, &ProcessEntry);
	}
	CloseHandle(pHandle);
	return pids;
}
class AuthPers {
public:
	AuthPers(char* LOGIN, char* PWD, char* ROLE) {
		login = LOGIN;
		pass = PWD;
		role = ROLE;
	}
	void connect() {
		string buff = "start c:\\Users\\123\\Desktop\\elementclient.lnk startbypatcher nocheck game:cpw console:1 user:" + char_to_str(login) + " pwd:" + char_to_str(pass) + " role:" + char_to_str(role);
		system(buff.c_str());
		Sleep(10000);
	}
	char *login, *pass, *role;
	bool readytostart = false;
	bool istarted = false;
	bool blocked = false;
};

typedef vector<AuthPers*> Avec;
typedef vector<Person*> Pvec;

void check_is_started(Avec authvec, Pvec persons) {
	for (unsigned int i = 0; i < persons.size(); i++) {
		for (unsigned int j = 0; j < authvec.size(); j++) {
			if (wcscmp(str_to_wchar(authvec[j]->role), persons[i]->getName()) == 0) {
				authvec[j]->istarted = true;
			}
		}
	}
	for (unsigned int i = 0; i < authvec.size(); i++) {
		for (unsigned int j = 0; j < authvec.size(); j++) {
			if (i != j && authvec[i]->istarted && strcmp(authvec[i]->login, authvec[j]->login) == 0) {
				authvec[j]->blocked = true;
			}
		}
	}
}
int main() {
	int mainmenucounter = 0;
	int lastmenucounter = 0;
	HANDLE conhandle = GetStdHandle(STD_OUTPUT_HANDLE); //Хэндл консоли
	COORD c;
	vector <DWORD> persons_pids;
	vector <Person*> persons;
	
	cout << "Loading started clients." << endl;
	
	persons_pids = getPidsVec("elementclient.exe");
	
	if (persons_pids.size() == 0) {
		cout << "Clients not found." << endl;
		mainmenucounter = 2;
	}
	else {
		cout << persons_pids.size() << " clients was founded." << endl << endl;
		cout << "Getting information from working persons." << endl;
		for (unsigned int i = 0; i < persons_pids.size(); i++) {
			persons.push_back(new Person(persons_pids[i]));
			wcout << persons[i]->getName();
			cout << " was loaded." << endl;
		}
		mainmenucounter = 3;
	}

	cout << endl << "Loading authdata. We can connect to:" << endl;
	fstream auth ("names.txt");

	vector <AuthPers*> authvec;

	while (!auth.eof()) {
		char* bufflog = new char;
		char* buffpwd = new char;
		char* buffrole = new char;
		auth >> bufflog;
		auth >> buffpwd;
		auth >> buffrole;
		AuthPers* buff = new AuthPers(bufflog, buffpwd, buffrole);
		authvec.push_back(buff);
	}
	auth.close();

	check_is_started(authvec, persons);
	for (unsigned int i = 0; i < authvec.size(); i++) {
		cout << authvec[i]->role << " on " << authvec[i]->login << endl;
	}

	Sleep(1000);
	system("cls");

	int activepers = 0;
	bool iswritten = false;

	while (1) {
		switch (mainmenucounter)
		{
		case 2: { //Добавление персонажей
			if (!iswritten) {
				cout << "Whom you want to connect?" << endl << "[E]nable" << endl << "[D]isable" << endl << "[S]tart / [Q]uit to desktop";
				if (lastmenucounter == 3) {
					c.X = 9; c.Y = 1;
					SetConsoleCursorPosition(conhandle, c);
					cout << "/ 'C' to returning";
				}
				for (unsigned int i = 0; i < authvec.size(); i++) {
					c.X = 0; c.Y = 5 + i;
					SetConsoleCursorPosition(conhandle, c);
					cout << authvec[i]->role;
					c.X = 21;
					SetConsoleCursorPosition(conhandle, c);
					cout << "[ ]";
					iswritten = true;
				}
			}
			else {
				for (unsigned int i = 0; i < authvec.size(); i++) {
					c.X = 21; c.Y = 5 + i;
					SetConsoleCursorPosition(conhandle, c);
					if (authvec[i]->blocked) {
						cout << "[*]";
					}
					if (authvec[i]->readytostart && !authvec[i]->blocked) {
						cout << "[R]";
					}
					else if (authvec[i]->istarted && !authvec[i]->blocked) {
						cout << "[A]";
					}
					else if (i == activepers && !authvec[i]->blocked) {
						cout << "[_]";
					}
					else if (i != activepers && !authvec[i]->readytostart && !authvec[i]->blocked) {
						cout << "[ ]";
					}
				}
			}
			if ((GetAsyncKeyState(VK_DOWN) & 0x1) == 0x1 && activepers != authvec.size() - 1) {
				activepers += 1;
			}
			if ((GetAsyncKeyState(VK_UP) & 0x1) == 0x1 && activepers != 0) {
				activepers -= 1;
			}
			if ((GetAsyncKeyState('E') & 0x1) == 0x1 && authvec[activepers]->readytostart == false && authvec[activepers]->istarted == false) {
				authvec[activepers]->readytostart = true;
				for (unsigned int j = 0; j < authvec.size(); j++) {
					if (activepers != j && !strcmp(authvec[activepers]->login, authvec[j]->login)) {
						authvec[j]->blocked = true;
					}
				}
			}
			if ((GetAsyncKeyState('D') & 0x1) == 0x1 && authvec[activepers]->readytostart == true) {
				authvec[activepers]->readytostart = false;
				for (unsigned int j = 0; j < authvec.size(); j++) {
					if (activepers != j && !strcmp(authvec[activepers]->login, authvec[j]->login)) {
						authvec[j]->blocked = false;
					}
				}
			}
			if ((GetAsyncKeyState('S') & 0x1) == 0x1) {
				system("cls");
				iswritten = false;
				mainmenucounter = 3;
				cout << "Starting clients." << endl;
				for (unsigned int i = 0; i < authvec.size(); i++) {
					if (authvec[i]->readytostart) {
						authvec[i]->connect();
						authvec[i]->readytostart = false;
					}
				}
				cout << "Getting information from started clients." << endl;
				vector <DWORD> buff;
				buff = getPidsVec("elementclient.exe");
				for (unsigned int i = 0; i < buff.size(); i++) {
					for (unsigned int j = 0; j < persons.size();j++) {
						if (persons_pids[j] == buff[i]) {
							break;
						}
					}
					persons.push_back(new Person(buff[i]));
				}
				system("cls");
			}
			if ((GetAsyncKeyState('C') & 0x1) == 0x1 && lastmenucounter != 0) {
				system("cls");
				iswritten = false;
				mainmenucounter = 3;
			}
			break;
		}
		case 3: {
			if (!iswritten) {
				cout << "Person" << endl << "Name:";
				iswritten = true;
			}
			else {
				c.X = 6; c.Y = 1;
				SetConsoleCursorPosition(conhandle, c);
				wcout << persons[0]->getName();
			}
			if ((GetAsyncKeyState('2') & 0x1) == 0x1) {
				iswritten = false;
				mainmenucounter = 2;
				lastmenucounter = 3;
				system("cls");
			}
			break;
		default:
			break;
		}
		}
		if ((GetKeyState('Q') & 0x1) == 0x1) {
			break;
		}
	}
	return 0;
}