#include "son.h"
#include <iostream>

using namespace std;

int main(void){
	FATHER *p1 = new SON();
	FATHER *p2 = new SON();
	
	p2->setValue(32);
	
	if (*p1 == *p2)
		cout << "The same" << endl;
	else
		cout << "Not equal" << endl;
	
	p1->printMember();
	p2->printMember();
	
	return 0;
}