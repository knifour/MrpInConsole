#include <iostream>
#include <string.h>
#include "utf8.h"

using namespace std;
using namespace utf8;

int main(void){
	string a = "UTF8編碼";
	int len, codelen;
	
	if ((len=countChars(a, codelen)) >= 0){
	  cout << "字元數：" << len << endl;
		cout << "UTF8編碼總長度：" << codelen << endl;
	} else {
		cout << "字串含有不合法的utf8編碼" << endl;
	}
	
	uint8_t b[codelen+1];
	strcpy((char*)b, a.c_str());
	cout << "字串：" << b << endl;
	
	return 0;
}