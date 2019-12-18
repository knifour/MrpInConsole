#include <iostream>
#include <string>
#include <stdint.h> 
#include <util.h>
#include <tableset.h>

using namespace std;

int main(void){
	/*string tmp;
	int c = 30;
	ATTR b = (ATTR)c;
	char Buf[20];
	
	tmp = string(UL);
	for (int i=0; i<2; i++)
		tmp = tmp + string(HZ);
	tmp = tmp + string(UM);
	for (int i=0; i<4; i++)
		tmp = tmp + string(HZ);
	tmp = tmp + string(UR);
	
	cout << "列印寬度為：" << Utf8RealDLen(tmp) << endl;
	cout << tmp << endl;
	
	sprintf(Buf, "\x1B[48;5;%dm", 0);
	cout << Buf;
	
	cout << "\x1B[7m";
	for (int i=0; i<16; i++){
		sprintf(Buf, "\x1b[38;5;%dm", i);
		cout << Buf << "X";
	}
	cout << "\x1B[0m" << endl;
	
	for (int i=0; i<6; i++){
		for (int j=0; j<6; j++){
			for (int k=0; k<6; k++){
	      sprintf(Buf, "\x1B[38;5;%dm", 16+i*36+j*6+k);
				cout << Buf << "X";
			}
	  }
		cout << endl;
	}
	
	for (int i=232; i<256; i++){
		sprintf(Buf, "\x1B[38;5;%dm", i);
		cout << Buf << "X";
	}
	cout << "\x1B[0m" << endl;*/
	
	int lin, col;
	
	cout << "\x1B[10;5H";
	CurPos(lin, col);
	cout << "lin=" << lin << ", col=" << col << endl;
  return 0;
}