#ifndef __DATE_H
#define __DATE_H

#include <ctime>
#include <string>
#include <iostream>
#include <datetime.h>
#include <util.h>

using namespace std;

class DATE {
public:
	DATE();
	DATE(int, int, int);
	DATE(const DATE &);
	DATE(const DATETIME &);
	string toString (int) const;
	int getYear(void) const {return mYear;};
	int getMonth(void) const {return mMonth;};
	int getDay(void) const {return mDay;};
	int getDays(void) const {return mDays;};
	int getDayOfWeek(void) const {return (mDays%7);};
	
	// 運算子重載
	DATE operator =(const DATE source);
	DATE operator =(const DATETIME source);
	int  operator -(const DATE other);
	DATE operator +(const int day);
	DATE operator -(const int day);

private:
  // 每月份天數陣列(2月份天數會根據是不是閏年改變)
	int MONTHDAY[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
  // 成員變數
	int mDays; 					// 從西元元年年1月1日到現在的天數
	int mYear;
	int mMonth;
	int mDay;
	
	// 成員函數
  void setYMD(time_t);
	void setDays(void);
	void calcDay(DATE&, const int);
};

#endif