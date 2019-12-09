#include <iostream>
#include <string>
#include <stdint.h> 
#include <util.h>
#include <attr.h>
#include <tableset.h>

using namespace std;

int main(void){
	string tmp;
	int c = 30;
	ATTR b = (ATTR)c;
	
	tmp = string(UL);
	for (int i=0; i<2; i++)
		tmp = tmp + string(HZ);
	tmp = tmp + string(UM);
	for (int i=0; i<4; i++)
		tmp = tmp + string(HZ);
	tmp = tmp + string(UR);
	
	cout << "列印寬度為：" << Utf8RealDLen(tmp) << endl;
	cout << tmp << endl;
	
  return 0;
}