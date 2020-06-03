#ifndef __DATE_H
#define __DATE_H

#include <ctime>
#include <string>
#include <iostream>
#include <datetime.h>

using namespace std;

class DATE {
public:
	DATE();
	DATE(int, int, int);
	DATE(const DATE &);
	DATE(const DATETIME &);
	string toString(int);
	int getYear(void) {return mYear;};
	int getMonth(void) {return mMonth;};
	int getDay(void) {return mDay;};
	int getDayOfWeek(void) {return (mDays%7);};
	
	// 運算子重載
	DATE operator =(const DATE source);
	DATE operator =(const DATETIME source);
	int  operator -(const DATE other);
	DATE operator +(const int day);

private:
  // 成員變數
	int mDays; 					// 從西元元年年1月1日到現在的天數
	int mYear;
	int mMonth;
	int mDay;
	
	// 成員函數
  void setYMD(time_t);
	void setDays(void);
	bool isLeap(int);
};

#endif