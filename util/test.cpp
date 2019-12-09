#include <stdio.h>
#include <iostream>
#include <string>
#include <screen.h>
#include <util.h>

using namespace std;

int main(void){
	SCREEN scr;
	char buf[10];
	int lin, pos, len;
	char key;

  scr.cls();
  scr.Locate(1, 1);
	scr.SetColor(ATTR::HRed, ATTR::BBlue);
	cout << "繽紛\n";
	scr.SetColor(ATTR::HYellow);
	scr.GetConsoleSize(lin, pos);
	printf("Lines = %d, Columns = %d\n", lin, pos);
	cout << "Press a key...";
	
	key=getch();
	len=Utf8Len(key);
	buf[0] = key;
	for (int i=1; i<len; i++){
		buf[i] = getch();
	}
	buf[len] = 0;
	cout << "\n" << buf << "\n";
	
  scr.ResetAttr();
	
	return 0;
}