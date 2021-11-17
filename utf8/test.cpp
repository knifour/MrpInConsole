#include <iostream>
#include <fstream>
#include <string>
#include "utf8.h"

using namespace std;
using namespace utf8;

int main(void){
	char src[] = "繽紛\n景觀\n資材";
	char target[] = "\n";

  cout << countStr(src, target) << endl;
	
	return 0;
}