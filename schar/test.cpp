#include <utf8schar.h>
#include <iostream>

#define LINS 25
#define COLS 80

int main(){
	uint8_t tmp[] = "紛";
	SCHAR *a = new UTF8SCHAR("繽");
	
	a->print();
	a->setChar(tmp, false, 9, 0);
	a->setFColor(ATTR::HYELLOW);
	a->print();
	std::cout << "\n";
	return 0;
}