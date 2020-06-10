#include <tptime.h>
#include <iostream>

void delay(int);

using namespace std;

int main(void){
	string dname[7] = {"日", "一", "二", "三", "四", "五", "六"};
	TPTIME now;
	TPTIME noon(12, 0, 0);

  cout << "現在時間" << now.toString() << endl;
	cout << "到中午還有" << noon-now << "秒鐘" << endl;
	
	return 0;
}

void delay(int sec){
	time_t start_time, cur_time;
	
	time(&start_time);
	do {
		time(&cur_time);
	} while ((cur_time-start_time)<sec);
}