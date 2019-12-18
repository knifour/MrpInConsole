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
	ms.SetActive(false);
	ms.cls();
	ms.PrintFromFile("../ncurses/cuscre.win");
	ms.SetActive(true);
	
	/*end = clock();
	cputime = (end-start)/CLOCKS_PER_SEC;
	ms.Locate(25, 1);
	sprintf(buf, "total time = %lf", cputime);
	ms.print((uint8_t*)buf);*/
	ms.SetActive(false);
	ms.SetFColor(11);
	ms.Locate(6, 17);
	ms.SetUnderLine(true);
	ms.print("A001");
	ms.Locate(6, 29);
	ms.print("中區");
	ms.SetUnderLine(false);
	ch = getch();
	ms.SetActive(true);
	cursor(false);
	
	ch = getch();
	cursor(true);
	return 0;
}