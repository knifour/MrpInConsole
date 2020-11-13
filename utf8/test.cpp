#include <iostream>
#include <string.h>
#include "utf8.h"

using namespace std;
using namespace utf8;

int main(void){
	string a = "U碼";
	uint8_t b[] = "";

  cout << getFirstDisplayLength(b) << endl;  
	
	return 0;
}