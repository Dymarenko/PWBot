#include "person.h"
#include "addr.h"
#include <iostream>
Person::Person(){
	prc = new Process;
	reInit();
}
void Person::get(){
	std::wcout << "Name:" << Name << "\n";
	std::cout << "X:" << x << "\t" << "HP:" << HP << "\n";
	std::cout << "Y:" << y << "\t" << "MP:" << MP << "\n";
	std::cout << "Z:" << z << "\n";
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
	Name = prc->readMem_8s(prc->readMem(prc->jumpToPersStruct() + PersName) + 0x0);
}
