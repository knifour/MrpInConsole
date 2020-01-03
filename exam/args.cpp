#include <stdio.h>
#include <stdarg.h>

using namespace std;

class Win{
public:
  Win(const char *fmt, ...);
	void print(void);

private:
  int mLin, mCol;
  int mLINS, mCOLS;	
};

Win::Win(const char *fmt, ...){
	va_list ap;
	int result;
	
	mLin = 1;
	mCol = 1;
	mLINS = 3;
	mCOLS = 6;
	
	va_start(ap, fmt);
	while (*fmt){
		switch (*fmt++){
		case 'l':
		  result = va_arg(ap, int);
			if (result < 1)
				result = 1;
			if (result > 24)
				result = 24;
			mLin = result;
			break;
		case 'c':
		  result = va_arg(ap, int);
			if (result < 1)
				result = 1;
			if (result > 80)
				result = 80;
			mCol = result;
			break;
		case 'L':
		  result = va_arg(ap, int);
			if (result < 1)
				result = 1;
			if (result > 30)
				result = 30;
		  mLINS = result;
			break;
		case 'C':
		  result = va_arg(ap, int);
			if (result < 1)
				result = 1;
			if (result > 100)
				result = 100;
			mCOLS = result;
			break;	
		}
	}
	va_end(ap);
}

void Win::print(void){
	printf("lin = %d\n", mLin);
	printf("column = %d\n", mCol);
	printf("Lines = %d\n", mLINS);
	printf("Columns = %d\n", mCOLS);
}

int main(void){
	Win aw("lcLC", 10, 21, 10, 20);
	
	aw.print();
	
  return 0;
}