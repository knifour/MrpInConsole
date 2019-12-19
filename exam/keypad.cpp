#include <iostream>
#include <stdint.h> 
#include <stdio.h>
#include <util.h>
#include <keypad.h>

using namespace std;

int main(void){
	int key=0;
	char ch;
	
	while (key != ESC){
		ch = input(key);
		if (ch != 0)
			printf("%c", ch);
		else
			printf("key=%d\n", key);
	}
	
  return 0;
}