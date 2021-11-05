#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>
#include <iostream>

using namespace std;

int main(){
	char buf[1024];
	char buf2[30];
	char *ap = buf2;
	char *clearstr, *gotostr, *standstr, *stendstr;
	
	tgetent(buf, getenv("TERM"));
	
	clearstr = tgetstr("cl", &ap);
	gotostr = tgetstr("cm", &ap);
	standstr = tgetstr("so", &ap);
	stendstr = tgetstr("se", &ap);
	
	fputs(clearstr, stdout);
	fputs(tgoto(gotostr, 20, 10), stdout);
	//printf("\x1B[31m您好, \x1B[0m");
	cout << "\x1B[31m您好， \x1B[0m";
	fputs(standstr, stdout);
	printf("世界");
	fputs(stendstr, stdout);
	putchar('!');
	
	return 0;
}

/*#include <iostream>
#include <fstream>
#include <iconv.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "tableset.h"

using namespace std;

int main(void){
	char SPC[] = "  ";
	
	for (int i=0; i<7; i++){
		for (int j=0; j<18; j++){
			switch (i){
			case 0:
			  if (j%2==0){
					if (j==0)
						cout << UL;
					else if (j==8)
						cout << UM;
					else if (j==16)
						cout << UR;
					else
						cout << HZ;
				}
				break;
			case 1:
			case 3:
			case 4:
			case 5:
			  if (j%2==0){
					if (j==0|j==8|j==16)
						cout << VT;
					else
						cout << SPC;
				}
				break;
			case 2:
			  if (j%2==0){
					if (j==0)
						cout << ML;
					else if (j==8)
						cout << MM;
					else if (j==16)
						cout << MR;
					else
						cout << HZ;
				}
			  break;
			case 6:
			  if (j%2==0){
					if (j==0)
						cout << DL;
					else if (j==8)
						cout << DM;
					else if (j==16)
						cout << DR;
					else
						cout << HZ;
				}
			  break;
		  }
	  }
		cout << endl;
	}
	
	return 0;
	
	/*fstream src("/home/supervisor/data/COBOL/BF/BSE/PARCRE.WIN", ifstream::in);
	string buf, dst;
	int status;
	
	while(getline(src, buf)){
		for (int i=0; i<buf.length(); i++){
			if (buf[i] == 13){
				buf.erase(i, 1);
				break;
			}
		}
		dst = convertBig5toUtf8(buf, &status);
		if (status == 0){
			cout << dst << endl;
		} else {
			cout << status << endl;
		}
	}
	
	src.close();
	return 0;
}*/