#include "person.h"
#include "addr.h"
Person::Person(){
	*prc = new Process;
	HP = prc->readMem(BaseAddr + PersStruct + PersHP);
}