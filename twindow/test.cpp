#include <twmain.h>
#include <util.h>
#include <kbmap.h>
#include <string>
#include <iostream>

using namespace std;

int main(void){
	TERMINAL<UTF8SCHAR> t;
	TWMAIN<UTF8SCHAR> tmain(&t);
	
	WIN win;
	
	win.Lin = win.Col = 1;
	win.Lins = win.Cols = 1;
	tmain.TWin2Term(win);
	char c=getch();
	return 0;
}