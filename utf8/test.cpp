#include <iostream>
#include <fstream>
#include <string>
#include "utf8.h"

using namespace std;
using namespace utf8;

int main(void){
	//string a = "不織布尺寸54\"x91.4m;每捲125平方公尺";
	//uint8_t a[] = {0xE7, 0xB7, 0xA8, 0xE7, 0xA2, 0xBC};
	fstream src;
	string buf;
	int len;

	src.open("../CJK.txt", ios::in);
	if (!src)
		return -1;
	
	while (getline(src, buf)){
		cout << "原字串：" << buf << endl;
		cout << "字元數：" << countChars(buf, len) << endl;
		cout << "編碼總長度：" << len << endl;
		cout << "螢幕顯示寬度：" << getDisplayLength(buf) << endl;
	}
	
	return 0;
}