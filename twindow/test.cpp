#include <twmain.h>
#include <util.h>
#include <kbmap.h>
#include <string>
#include <iostream>

using namespace std;

int main(void){
	TERMINAL<UTF8SCHAR> t;
	TWMAIN<UTF8SCHAR> tmain(&t);

	int code=0;
	string buf;
	showCursor();
	tmain.locate(1, 5);
	buf = input(code);
	if (code==0)
		cout << buf << endl;
	
	return 0;
}