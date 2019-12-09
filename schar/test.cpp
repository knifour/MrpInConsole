#include <utf8schar.h>
#include <iostream>

#define LINS 25
#define COLS 80

int main(){
	uint8_t tmp[] = "紛";
	SCHAR *a = new UTF8SCHAR("繽");
	
	a->print();
	a->SetChar(tmp);
	a->SetFColor(ATTR::HRed);
	a->print();
	std::cout << "\n";
	return 0;
}