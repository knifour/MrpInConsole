#include <stdio.h>
#include <time.h>
#include <string>
#include <fstream>
#include <screen.h>
#include <util.h>
#include <iostream>

int main(void){
	SCREEN ms(15, 4);
	double start, end;
	double cputime;
	char buf[80];
	char ch;
	
	/*start = clock();*/
	ms.setActive(false);
	ms.cls();
	ms.printFromFile("menu.scr");
	/*ms.setActive(true);*/
	
	/*end = clock();
	cputime = (end-start)/CLOCKS_PER_SEC;
	ms.locate(25, 1);
	sprintf(buf, "total time = %lf", cputime);
	ms.print((uint8_t*)buf);*/
	/*ms.setActive(false);*/
	hideCursor();
	ms.setFColor(11);
	ms.locate(6, 17);
	ms.setUnderLine(true);
	ms.print("A001");
	ms.locate(6, 29);
	ms.print("中區");
	ms.setUnderLine(false);
	ms.setActive(true);
	
	ch = getch();
	showCursor();
	return 0;
}