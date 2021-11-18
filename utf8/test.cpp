#include <iostream>
#include <fstream>
#include <string>
#include "utf8.h"

using namespace std;
using namespace utf8;

int main(void){
	vector<string> buf;

  int cnt=splitStr("192.168.0.7", ".", buf);
	for (auto it=buf.begin(); it!=buf.end(); it++)
		cout << *it << endl;
	
	return 0;
}