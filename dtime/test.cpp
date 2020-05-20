#include <datetime.h>
#include <iostream>

using namespace std;

int main(void){
	string dname[7] = {"日", "一", "二", "三", "四", "五", "六"};
	DATETIME now;
	
	cout << now.getDateString(1) << endl;
	cout << now.getTimeString(0) << endl;
	cout << "今天是中華民國" << now.getYear()-1911 << "年";
	cout << now.getMonth() << "月";
	cout << now.getDay() << "日";
	cout << "星期" << dname[now.getDayOfWeek()] << endl;
	cout << "現在是" << now.getHour() << "點";
	cout << now.getMinute() << "分";
	cout << now.getSecond() << "秒" << endl;
	
	return 0;
}