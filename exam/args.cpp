#include <stdio.h>
#include <stdarg.h>

using namespace std;

/* l = lin, 
   c = col, 
	 L = LINES, 
	 C = COLUMNS */
void para(const char *fmt, ...);

int main(void){
	
	para("clC", 7, 31, 28);
	
  return 0;
}

void para(const char *fmt, ...){
	va_list ap;
	int result;
	
	va_start(ap, fmt);
	while (*fmt){
		switch (*fmt++){
		case 'l':
		  result = va_arg(ap, int);
			printf("line=%d\n", result);
			break;
		case 'c':
		  result = va_arg(ap, int);
			printf("column=%d\n", result);
			break;
		case 'L':
		  result = va_arg(ap, int);
			printf("Lines=%d\n", result);
			break;
		case 'C':
		  result = va_arg(ap, int);
			printf("Columns=%d\n", result);
			break;
		}
	}
	va_end(ap);
}