#include <stdio.h>
#include <time.h>
#include <string>
#include <fstream>
#include <screen.h>
#include <util.h>

int main(void){
	SCREEN ms(15, 4);
	/*double start, end;
	double cputime;*/
	char ch;
	
	/*start = clock();*/
	ms.cls();
	ms.SetActive(false);
	ms.PrintFromFile("../ncurses/cuscre.win");
	ch = getch();
	ms.refresh();
	
	/*end = clock();
	cputime = (end-start)/CLOCKS_PER_SEC;
	main.SetColor(ATTR::HYellow);
	main.Locate(2, 1);
	sprintf(buf, "total time = %lf", cputime);
	main.print((uint8_t*)buf);*/
	
	ch = getch();
	return 0;
}