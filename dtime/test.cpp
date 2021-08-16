#include <date.h>
#include <ltime.h>
#include <iostream>

void delay(int);

using namespace std;

int main(void){
	string dname[7] = {"日", "一", "二", "三", "四", "五", "六"};
	DATE now;
	LTIME t1, t2(16, 30, 0);

  cout << "中華民國" << now.toString(MINGSLASH);
	cout << "星期" << dname[now.getDayOfWeek()] << endl;
	cout << (t2-t1)/60 << "分" << (t2-t1)%60 << "秒" << endl;
	
	return 0;
}

void delay(int sec){
	time_t start_time, cur_time;
	
	time(&start_time);
	do {
		time(&cur_time);
	} while ((cur_time-start_time)<sec);
}