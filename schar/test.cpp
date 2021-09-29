#include <utf8schar.h>
#include <iostream>

#define LINS 25
#define COLS 80

using namespace std;

void printChar(SCHAR*);

int main(){
	SCHAR* a = new UTF8SCHAR("繽",  9, 4);
	SCHAR* b = new UTF8SCHAR("紛",  9, 4);
	SCHAR* c = new UTF8SCHAR("景",  9, 4);
	SCHAR* d = new UTF8SCHAR("觀",  9, 4);
	
	b->setFColor(ATTR::RED);
	b->setUnderLine(true);
	c->setBColor(ATTR::RED);
	c->setFColor(ATTR::HWHITE);
	
	a->printMember();
	b->printMember();
	c->printMember();
	d->printMember();
	
	if (*a == *c)
	  cout << "a與c相同" << endl;
		
	if (*b == *d)
	  cout << "b與d相同" << endl;
		
	/* cout << *a << *b << *c << *d << endl; */
	
	printChar(a);
	printChar(b);
	printChar(c);
	printChar(d);
	cout << endl;
	
	return 0;
}

void printChar(SCHAR* c){
	char Buf[60];
	
	if (c->isValid()){
		if (c->getUnderLine())
			cout << "\x1B[4m";
	  else
			cout << "\x1B[24m";
	}
		
	/*sprintf(Buf, "\x1B[48;5;%dm", c->getBColor());
	cout << Buf;
	sprintf(Buf, "\x1B[38;5;%dm", c->getFColor());
	 cout << Buf;
   cout << c->getChar() << "\x1B[0m";*/
		
	sprintf(Buf, "\x1B[48;5;%dm\x1B[38;5;%dm%s\x1B[0m", c->getBColor(), c->getFColor(), c->getChar().c_str());
	cout << Buf;	
}