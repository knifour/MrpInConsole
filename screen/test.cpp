#include <stdio.h>
#include <time.h>
#include <screen.h>
#include <util.h>

int main(void){
	SCREEN main(ATTR::FWhite, ATTR::BBlue);
	char buf[300];
	double start, end;
	double cputime;
	char ch;
	
	start = clock();
	main.cls();
	main.SetActive(true);
	main.print((uint8_t*)"繽紛景觀資材有限公司");
	end = clock();
	cputime = (end-start)/CLOCKS_PER_SEC;
	main.SetColor(ATTR::HYellow);
	main.Locate(2, 1);
	sprintf(buf, "total time = %lf", cputime);
	main.print((uint8_t*)buf);
	
	ch = getch();
	return 0;
}