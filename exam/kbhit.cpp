/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <util.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <kbmap.h>

using namespace std;

int main(int argc, char** argv) {
	int funckey;
	string temp="";
	
  printf("Press any key\n");
	temp = input(funckey);
  if (funckey!=0){
		cout << "特殊按鍵代碼：" << funckey << endl;
	} else {
		if (temp.length()!=0)
			cout << "按鍵值：" << temp << endl;
		else
			cout << "按鍵未定義" << endl;
	}
	
  return 0;
}