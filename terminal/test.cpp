#include <terminal.h>
#include <utf8schar.h>

int main(){
	TERMINAL<UTF8SCHAR> main;
	
	main.reflash();
	getch();
}