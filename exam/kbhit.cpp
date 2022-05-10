/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <util.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <keymap.h>
#include <keypad.h>

using namespace std;

int main(int argc, char** argv) {
	int funckey=0;
	string temp="";
	
  printf("Press any key\n");
	while (1) {
	  temp = input(funckey);
		if (funckey==ESC)
			break;
		if (funckey!=0){
			cout << "按鍵代碼：" << funckey << endl;
		  cout << "按鍵名稱：" << KEYNAME[funckey] << endl;
		} else {
			if (temp.length()!=0)
				cout << "按鍵值：" << temp << endl;
			else
				cout << "按鍵未定義" << endl;
		}
	}
	
  return 0;
}