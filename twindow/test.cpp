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

  tmain.printFromFile("menu.scr");
	tmain.locate(5, 16);
	tmain.setBColor(ATTR::BLUE);
	tmain.setFColor(ATTR::RED);
	tmain.print("零件資料管理");
	tmain.locate(7, 16);
	tmain.print("客戶資料管理");
	tmain.locate(8, 16);
	tmain.print("廠商資料管理");
	tmain.locate(6, 16);
	tmain.setFColor(ATTR::HRED);
	tmain.print("產品資料管理");
	input(code);
	
	return 0;
}