/*#include <ncurses.h>
#include <locale.h>*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main(void){
	fstream scr1;
	string str;
	
	/*setlocale(LC_ALL, "");
	initscr();*/
	
	scr1.open("cuscre.win", ios::in);
	while (getline(scr1, str)){
	  cout << str << "\r\n";
		/*printw(str.c_str());
		printw("\n");*/
	}
	scr1.close();
	/*getch();
	
	endwin();*/
	return 0;
}