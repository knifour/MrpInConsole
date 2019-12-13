#include <stdio.h>
#include <time.h>
#include <string>
#include <fstream>
#include <screen.h>
#include <util.h>

int main(void){
	SCREEN ms(ATTR::FWhite, ATTR::BBlue);
	/*double start, end;
	double cputime;*/
	char ch;
	
	/*start = clock();*/
	ms.cls();
	ms.SetActive(true);
	ms.PrintFromFile("../ncurses/cuscre.win");
	
	/*end = clock();
	cputime = (end-start)/CLOCKS_PER_SEC;
	main.SetColor(ATTR::HYellow);
	main.Locate(2, 1);
	sprintf(buf, "total time = %lf", cputime);
	main.print((uint8_t*)buf);*/
	
	ch = getch();
	return 0;
}