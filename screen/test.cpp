#include <stdio.h>
#include <time.h>
#include <string>
#include <fstream>
#include <screen.h>
#include <util.h>
#include <iostream>

int main(void){
	SCREEN ms(15, 4);
	/*double start, end;
	double cputime;*/
	char ch;
	
	/*start = clock();*/
	ms.SetActive(false);
	ms.cls();
	ms.Locate(1, 1);
	for (int i=77; i<=80; i++){
		ms.printcode(5, i);
	}
	ms.PrintFromFile("../ncurses/cuscre.win");
	ch = getch();
	ms.SetActive(true);
	ch = getch();
	ms.Locate(1, 1);
	for (int i=77; i<=80; i++){
		ms.printcode(5, i);
	}
	
	/*end = clock();
	cputime = (end-start)/CLOCKS_PER_SEC;
	main.SetColor(ATTR::HYellow);
	main.Locate(2, 1);
	sprintf(buf, "total time = %lf", cputime);
	main.print((uint8_t*)buf);*/
	
	ch = getch();
	return 0;
}