#include <iostream>
#include <fstream>
#include <string>
#include "utf8.h"

using namespace std;
using namespace utf8;

int main(void){
	string a = "圓腳3公分排水板";
	uint8_t buf[100];
	//uint8_t a[] = {0xE7, 0xB7, 0xA8, 0xE7, 0xA2, 0xBC};
	
	cout << "原字串：" << a << endl;
	cout << "擷取中間字串(3, 3)：" << getMidStr(a, 3, 3) << endl;
	cout << "擷取中間字串且超過原字串長度(6, 6)：" << getMidStr(a, 6, 6) << endl;
	cout << "擷取左字串(2)：" << getLeftStr(a, 2) << endl;
	cout << "攫取左字串且超過原字串長度(10)：" << getLeftStr(a, 10) << endl;
	cout << "攫取右字串(6)：" << getRightStr(a, 6) << endl;
	cout << "攫取右字串且超過原字串長度(20)：" << getRightStr(a, 20) << endl;
	
	return 0;
}