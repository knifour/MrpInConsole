#include <twmain.h>
#include <util.h>
#include <kbmap.h>
#include <string>
#include <iostream>

using namespace std;

int main(void){
	int code;
	
	TERMINAL<UTF8SCHAR> t;
	TWMAIN<UTF8SCHAR> tmain(&t);

  tmain.locate(10, 11);
	tmain.setFColor(ATTR::HRED);
	tmain.print("測試");
	input(code);
	tmain.locate(10, 61);
	tmain.setBColor(ATTR::BLUE);
	tmain.print("繽紛景觀資材有限公司");
	input(code);
	
	return 0;
}