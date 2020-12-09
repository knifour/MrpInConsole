#include <utf8schar.h>
#include <iostream>

#define LINS 25
#define COLS 80

using namespace std;

int main(){
	UTF8SCHAR a("繽",  9, 4);
	UTF8SCHAR b("紛",  9, 4);
	UTF8SCHAR c("景",  9, 4);
	UTF8SCHAR d("觀",  9, 4);
	
	b.setFColor(ATTR::HYELLOW);
	c.setBColor(ATTR::RED);
	c.setFColor(ATTR::HWHITE);
	
	a.printMember();
	b.printMember();
	c.printMember();
	d.printMember();
	
	if (a == c)
	  cout << "a與c相同" << endl;
		
	if (b == d)
	  cout << "b與d相同" << endl;
		
	cout << a << b << c << d << endl;
	
	return 0;
}