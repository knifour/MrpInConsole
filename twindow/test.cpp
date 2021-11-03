#include <twmain.h>
#include <util.h>
#include <kbmap.h>
#include <string>
#include <iostream>

using namespace std;

int main(void){
	TERMINAL<UTF8SCHAR> t;
	TWMAIN<UTF8SCHAR> tmain(&t);
	
	tmain.locate(1, 1);
	
	string buf;
	int code = 0;
	
	while(code!=ESC){
		buf = input(code);
	  cout << buf << endl;
	}
	
	return 0;
}