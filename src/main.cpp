#include "person.h"
#include <locale>
int main() {
	setlocale(LC_ALL, "");
	Person *per = new Person;
	for (int i = 0; i< 1E04; i++)
	{
		per->get();
		
		system("cls");
	}
	system("PAUSE");
	return 0;
}
