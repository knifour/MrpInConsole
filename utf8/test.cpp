#include <iostream>
#include <fstream>
#include <string>
#include "utf8.h"

using namespace std;
using namespace utf8;

int main(void){
	char src[] = "繽紛\n景觀\n資材";
	char target[] = "\n";
	vector<string> buf;

  int cnt=splitStr(src, target, buf);
	cout << cnt << endl;
	for (auto it=buf.begin(); it!=buf.end(); it++)
		cout << *it << endl;
	
	return 0;
}