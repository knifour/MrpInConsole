#include <iostream>
#include "utf8.h"

using namespace std;
using namespace utf8;

int main(void){
	string a = "";
	uint8_t b[] = {0xE5, 0x07};
	int len;
	
	if (countChars(a, len))
	  cout << "字串a長度為" << len << endl;
	else
		cout << "字串含有不合法的utf8編碼" << endl;
	
	return 0;
}