#include <utf8schar.h>
#include <iostream>

#define LINS 25
#define COLS 80

using namespace std;

int main(){
	uint8_t tmp[] = "紛";
	SCHAR* a = new UTF8SCHAR("繽");
	SCHAR* b = new UTF8SCHAR("紛");
	
	a->print();
	b->print();
	cout << endl;
	
	if (*a == *b)
		cout << "相同" << endl;
	else
		cout << "不同" << endl;
	
	*a = *b;
	
	a->print();
	b->print();
	cout << endl;
	
	if (*a == *b)
		cout << "相同" << endl;
	else
		cout << "不同" << endl;
	
	return 0;
}