#ifndef __DATETIME_H
#define __DATETIME_H

#include <ctime>
#include <string>
#include <iostream>
#include <stdint.h>

using namespace std;

#define OLDDAYS 719163  // 到1970年1月1日的天數(西元元年1月1日算第1天)

class DATETIME {
public:
	DATETIME();
	DATETIME(int, int, int);
	DATETIME(int, int, int, int, int, int);
	string getDateString(int);
	string getTimeString(void);
	int getYear(void) {return mYear;};
	int getMonth(void) {return mMonth;};
	int getDay(void) {return mDay;};
	int getHour(void) {return mHour;};
	int getMinute(void) {return mMinute;};
	int getSecond(void) {return mSecond;};
	int getDayOfWeek(void) {return (mOrigin/86400+4)%7;};
	
	// 運算子重載
	DATETIME operator =(DATETIME source);
	bool operator ==(DATETIME other);
	bool operator >(DATETIME other);
	bool operator <(DATETIME other);
	int operator -(DATETIME other);

private:
  // 成員變數
	time_t mOrigin; 					// 從1970年1月1日到現在的秒數(台北時間)
	int mYear;
	int mMonth;
	int mDay;
	int mHour;
	int mMinute;
	int mSecond;
	
	// 成員函數
  void getYMD(void);
  void getHMS(void);
	void setOrigin(void);
	bool isLeap(int);
};

#endif