#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main(){
	vector<string> a;
	string name;

  while (1){
		getline(cin, name);
		if (name.empty())
			break;
		else
			a.push_back(name);
	}
	
	for (vector<string>::iterator it=a.begin(); it!=a.end(); it++)
		cout << *it << endl;
	
	return 0;
}