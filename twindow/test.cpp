#include <twmain.h>
#include <util.h>
#include <kbmap.h>
#include <string>
#include <iostream>

using namespace std;

int main(void){
	TERMINAL<UTF8SCHAR> t;
	TWMAIN<UTF8SCHAR> tmain(&t);

	int code=0, cnt = 11;
	string buf;
	
	while (code!=ESC){
		tmain.locate(cnt, 11);
	  buf = input(code);
	  if (code==0){
		  cout << buf;
			cnt++;
			if (cnt>tmain.getLINS())
				break;
		}
	}
	cout << endl;
	
	return 0;
}