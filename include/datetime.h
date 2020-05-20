#ifndef __DATETIME_H
#define __DATETIME_H

#include <ctime>
#include <string>
#include <iostream>

using namespace std;

class DATETIME {
public:
	DATETIME();
	string getDateString(int);
	string getTimeString(int);
	int getYear(void) {return mYear;};
	int getMonth(void) {return mMonth;};
	int getDay(void) {return mDay;};
	int getHour(void) {return mHour;};
	int getMinute(void) {return mMinute;};
	int getSecond(void) {return mSecond;};
	int getDayOfWeek(void) {return (mOrigin/86400+4)%7;};

private:
  // 成員變數
	time_t mOrigin; 					// 從1970年1月1日到現在的秒數
	int mYear;
	int mMonth;
	int mDay;
	int mHour;
	int mMinute;
	int mSecond;
	
	// 成員函數
  void getYMD(void);
  void getHMS(void);
	bool isLeap(int);
};

#endif