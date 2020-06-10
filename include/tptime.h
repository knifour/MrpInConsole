#ifndef __TPTIME_H
#define __TPTIME_H

#include <ctime>
#include <string>
#include <iostream>
#include <util.h>

using namespace std;

class TPTIME {
public:
	TPTIME();
	TPTIME(int, int, int);
	TPTIME(const TPTIME &);
	string toString () const;
	int getHour(void) const {return mHour;};
	int getMinute(void) const {return mMinute;};
	int getSecond(void) const {return mSecond;};
	int getSeconds(void) const {return mSeconds;};
	
	// 運算子重載
	TPTIME operator =(const TPTIME source);
	bool operator ==(const TPTIME source);
	bool operator >(const TPTIME source);
	bool operator <(const TPTIME source);
	int  operator -(const TPTIME other);
	TPTIME operator +(const int day);
	TPTIME operator -(const int day);

private:
  // 成員變數
	int mSeconds; 					// 從西元元年年1月1日到現在的天數
	int mHour;
	int mMinute;
	int mSecond;
	
	// 成員函數
  void setHMS(time_t);
	void setSeconds(void) {mSeconds = mHour*3600+mMinute*60+mSecond;};
	void calcSecond(TPTIME&, const int);
};

#endif