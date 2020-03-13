#include <stdio.h>
#include <iostream>
#include <string>
#include <screen.h>
#include <util.h>

using namespace std;

int main(void){
	unsigned char ch;
	
  hideCursor();
	ch = getch();
	cout << ch << endl;
	showCursor();
  
	return 0;
}