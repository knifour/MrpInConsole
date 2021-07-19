#include "son.h"
#include <iostream>

using namespace std;

int main(void){
	FATHER *p1 = new SON();
	FATHER *p2 = new SON();
	FATHER *p3 = new SON();
	
	if (*p1 == *p2)
		cout << "The same" << endl;
	else
		cout << "Not equal" << endl;
	
	p2->setSon(8);
	
	if (*p1 == *p2)
		cout << "The same" << endl;
	else
		cout << "Not equal" << endl;
	
	*p3 = *p2;
	
	if (*p2 == *p3)
		cout << "The same" << endl;
	else
		cout << "Not equal" << endl;
	
	p1->printMember();
	p2->printMember();
	p3->printMember();
	
	return 0;
}