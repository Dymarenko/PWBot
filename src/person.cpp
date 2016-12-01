#include "person.h"
#include "addr.h"
#include <iostream>
#include <clocale>

Person::Person(DWORD PID){
	prc = new Process(PID);
	reInit();
}
void Person::reInit()
{
	HP = prc->readMem(prc->jumpToPersStruct() + PersHP);
	MP = prc->readMem(prc->jumpToPersStruct() + PersMP);
	x = prc->readMem_f(prc->jumpToPersStruct() + PersXcoord) / 10 + 400;
	y = prc->readMem_f(prc->jumpToPersStruct() + PersYcoord) / 10 + 551;
	z = prc->readMem_f(prc->jumpToPersStruct() + PersZcoord) / 10;
	Lvl = prc->readMem(prc->jumpToPersStruct() + PersLvl);
	wcscpy(Name, prc->readMem_20s(prc->readMem(prc->jumpToPersStruct() + PersName) + 0x0));
	Med = prc->readMem_b(prc->jumpToPersStruct() + PersMedF);
	invC = prc->readMem(prc->jumpToPersInventory() + InvCount);
	targetWID = prc->readMem(prc->jumpToPersStruct() + 0xD3C);
}
wchar_t* Person::getName() {
	reInit();
	return Name;
}
DWORD Person::getHP() {
	return HP;
}
float Person::getX() {
	return x;
}
float Person::getY() {
	return y;
}
float Person::getZ() {
	return z;
}