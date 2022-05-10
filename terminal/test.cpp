#include <terminal.h>
#include <utf8schar.h>
#include <attr.h>

int main(){
	TERMINAL<UTF8SCHAR> main(ATTR::HRED, ATTR::BLUE);
	SCHAR* sp;
	uint8_t c[] = "A";
	
	getch();

  for (int i=8; i<=17; i++)
    for (int j=36; j<=45; j++){
			sp = main.getSP(i, j);
			sp->setChar(c, false, ATTR::RED, ATTR::BLUE);
		}
  main.reflash(8, 36, 10, 10);		
	
	getch();
}