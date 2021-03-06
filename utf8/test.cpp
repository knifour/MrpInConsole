#include <iostream>
#include <fstream>
#include <string>
#include "utf8.h"

using namespace std;
using namespace utf8;

int main(void){
	string a = "// 將原始字串中的特定字串取代成目標字串\n// 參數1：原始字串(uint8_t*)\n// 參數2：指定字串(uint8_t*)\n// 參數3：取帶字串(uint8_t*)\n// 參數4：true -> 全部取代，false -> 只取代第一個(可省略，表示全部取代)\n// 回傳值：取代後的字串(string)\n";
	//string a = "// 用途：將原始字串中的特定字串取代成目標字串\n";
	string target = "(uint8_t*)";
	string replace = "(string&)";
	
  a = replaceStr(a, target, replace);	
	cout << a << endl;
	
	return 0;
}