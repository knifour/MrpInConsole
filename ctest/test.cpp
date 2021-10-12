#include "grandson.h"
#include <iostream>

using namespace std;

int main(void){
	FATHER *p1 = new GRANDSON();
	FATHER *p2 = new GRANDSON();
	FATHER *p3 = new GRANDSON();
	FATHER *p4 = new SON();
	
	if (*p1 == *p2)
		cout << "The same" << endl;
	else
		cout << "Not equal" << endl;
	
	p2->setGrandSon(8);
	p4->setSon(38);
	
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
	cout << p1->getSon() << endl;
	p3->printMember();
	p4->printMember();
	
	return 0;
}