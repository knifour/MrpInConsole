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

string getKeycode(int);

int main(int argc, char** argv) {
	int b;
	string temp;
	
  printf("Press any key\n");
	fflush(stdout);
	initTermios(0);
  while (!(b=_kbhit())) {
    /*printf(".");
    fflush(stdout); */
    usleep(1000);
  }
	resetTermios();
		
	string key = getKeycode(b);
	
	bool match = false;
	for (int i=0; i<MAPLENGTH; i++){
		if (key.compare(KEYMAP[i])==0){
			cout << i << endl;
			match = true;
		}
	}
	
	if (!match){
		cout << "按鍵代碼：";
		for (int i=0; i<key.length(); i++)
			printf("%x ",key[i]);
	  cout << endl;
	}
		
  return 0;
}