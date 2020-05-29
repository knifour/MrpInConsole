#include <date.h>
#include <iostream>

void delay(int);

using namespace std;

int main(void){
	string dname[7] = {"日", "一", "二", "三", "四", "五", "六"};
	DATE now;
  DATE newday = now;
	
	cout << now.toString(1) << endl;
	cout << "星期" << dname[now.getDayOfWeek()] << endl;
	cout << newday.toString(2) << endl;
	cout << "星期" << dname[newday.getDayOfWeek()] << endl;
  
	return 0;
}

void delay(int sec){
	time_t start_time, cur_time;
	
	time(&start_time);
	do {
		time(&cur_time);
	} while ((cur_time-start_time)<sec);
}