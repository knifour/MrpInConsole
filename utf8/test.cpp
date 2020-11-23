#include <iostream>
#include <fstream>
#include <string>
#include "utf8.h"

using namespace std;
using namespace utf8;

int main(void){
	string a = "材質：NYLON;尺寸(長寬)：5.9x2.6x12.5cm;說明：不織布交疊處建議10~15cm";
	string temp;
	
	cout << "字串顯示寬度：" << getDisplayLength(a) << endl;

  for (int i=1; i<=countChars(a); i++){
		temp = getMidStr(a, i, 1);
		cout << temp << " -> " << getFirstDisplayLength(temp) << endl;
	}	
	return 0;
}