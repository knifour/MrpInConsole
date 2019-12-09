#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <string.h>

using namespace std;

char HZ[] = "\xe2\x94\x80\x0";
char VT[] = "\xe2\x94\x82\x0";
char UL[] = "\xe2\x94\x8c\x0";
char UM[] = "\xe2\x94\xac\x0";
char UR[] = "\xe2\x94\x90\x0";
char ML[] = "\xe2\x94\x9c\x0";
char MM[] = "\xe2\x94\xbc\x0";
char MR[] = "\xe2\x94\xa4\x0";
char DL[] = "\xe2\x94\x94\x0";
char DM[] = "\xe2\x94\xb4\x0";
char DR[] = "\xe2\x94\x98\x0";

int main(){
	int i;
	string label("公司：");
	string ltd("繽紛景觀資材有限公司");
	string msg = label + ltd;
	string buf, temp;
	
	setlocale(LC_ALL, "");
	initscr();
	
	printw("%2s", UL);
	for (i=0; i<2; i++) printw("%s", HZ);
	printw("%2s", UM);
	for (i=0; i<4; i++) printw("%s", HZ);
	printw("%2s", UR);
	printw("\n");
	
	
	printw("%2s", VT);
	printw("編號");
	printw("%2s", VT);
	printw("姓    名");
	printw("%2s", VT);
	printw("\n");
	
	printw("%2s", ML);
	for (i=0; i<2; i++) printw("%s", HZ);
	printw("%2s", MM);
	for (i=0; i<4; i++) printw("%s", HZ);
	printw("%2s", MR);
	printw("\n");
	
	printw("%2s", VT);
	printw("0001");
	printw("%2s", VT);
	printw("張群勝  ");
	printw("%2s", VT);
	printw("\n");
	
	printw("%2s", DL);
	for (i=0; i<2; i++) printw("%s", HZ);
	printw("%2s", DM);
	for (i=0; i<4; i++) printw("%s", HZ);
	printw("%2s", DR);
	printw("\n");
	
	move(0, 18);
	printw(msg.c_str());
	printw("\n");
	
	getch();
	endwin();
	
	return 0;
}
