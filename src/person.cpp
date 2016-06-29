#include "person.h"
#include "addr.h"
#include <iostream>
#include <clocale>
Person::Person(){
	prc = new Process;
	reInit();
	system("pause");
}
void Person::get(){
	std::wcout << "Name:" << Name << "\n";
	std::cout << std::dec;
	std::cout << "X:" << x << "\t" << "HP:" << HP << "\t" << "Lvl:" <<Lvl << "\n";
	std::cout << "Y:" << y << "\t" << "MP:" << MP << "\n";
	std::cout << "Z:" << z << "\n";
	std::cout << std::hex << "Target:" << targetWID << "\n";
	std::cout << "Medit.:" << (bool)Med << "\n";
	reInit();
	Sleep(41);
}
void Person::reInit()
{
	HP = prc->readMem(prc->jumpToPersStruct() + PersHP);
	MP = prc->readMem(prc->jumpToPersStruct() + PersMP);
	x = prc->readMem_f(prc->jumpToPersStruct() + PersXcoord) / 10 + 400;
	y = prc->readMem_f(prc->jumpToPersStruct() + PersYcoord) / 10 + 551;
	z = prc->readMem_f(prc->jumpToPersStruct() + PersZcoord) / 10;
	Lvl = prc->readMem(prc->jumpToPersStruct() + PersLvl);
	Name = prc->readMem_9s(prc->readMem(prc->jumpToPersStruct() + PersName) + 0x0);
	Med = prc->readMem_b(prc->jumpToPersStruct() + 0x740);
	invC = prc->readMem(prc->jumpToPersInventory() + InvCount);
	targetWID = prc->readMem(prc->jumpToPersStruct() + 0xD3C);
}