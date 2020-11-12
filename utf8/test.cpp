#include <iostream>
#include "utf8.h"

using namespace std;
using namespace utf8;

int main(void){
	string a = "從UTF8編碼第一碼可以知道這個字的編碼總長度";
	uint8_t b[] = {0xE5, 0x07};
	int len;
	
	if ((len=countChars(a)) >= 0){
	  cout << "字串a長度為" << len << endl;
		cout << "編碼總長度：" << isUtf8((uint8_t*)a.c_str()) << endl;
	} else {
		cout << "字串含有不合法的utf8編碼" << endl;
	}
	
	return 0;
}