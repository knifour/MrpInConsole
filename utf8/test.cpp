#include <iostream>
#include <string.h>
#include "utf8.h"

using namespace std;
using namespace utf8;

int main(void){
	string a = "圓腳排水板35x35x3cm";
	int len;
	uint8_t buf[10];
	
	cout << "原字串：" << a << endl;
	cout << "字元數：" << countChars(a, len) << endl;
	cout << "UTF8編碼總長度：" << len << endl;
	cout << "螢幕顯示寬度：" << getDisplayLength(a) << endl;
	
	for (int i=1; i<=countChars(a); i++){
		cout << getMidStr(a, i, 1) << endl;
	}
	
	return 0;
}