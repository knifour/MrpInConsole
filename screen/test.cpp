#include <stdio.h>
#include <time.h>
#include <screen.h>
#include <util.h>

int main(void){
	SCREEN main(ATTR::FWhite, ATTR::BBlue);
	double start, end;
	double cputime;
	char ch;
	
	start = clock();
	main.cls();
	main.Locate(10, 1);
	main.SetAttr(ATTR::Underline);
	printf("螢幕總列數=%3d, 螢幕總行數=%3d\n", main.GetLins(), main.GetCols());
	main.SetColor(ATTR::HMagenta);
	main.SetAttr(ATTR::UnderlineOff);
	main.Locate(24, 1);
	printf("螢幕總列數=%3d, 螢幕總行數=%3d\n", main.GetLins(), main.GetCols());
	end = clock();
	cputime = (end-start)/CLOCKS_PER_SEC;
	main.SetColor(ATTR::HYellow);
	printf("total time = %lf\n", cputime);
	
	ch = getch();
	return 0;
}