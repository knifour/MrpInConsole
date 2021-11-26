#include <twmain.h>
#include <twmsgbox.h>
#include <util.h>
#include <kbmap.h>
#include <string>
#include <iostream>

using namespace std;

int main(void){
	int code;
	WIN win;
	char msg[] = "存檔完成!\n按任意鍵繼續...\n或按[F1]請求幫助";
	TERMINAL<UTF8SCHAR> t;
	TWMAIN<UTF8SCHAR> tmain(&t);
	tmain.show();
	win.FColor = ATTR::HWHITE;
	win.BColor = ATTR::RED;
	TWMSGBOX<UTF8SCHAR> mbox(&tmain, msg, win);
	
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
	mbox.show();
	input(code);
	
	return 0;
}