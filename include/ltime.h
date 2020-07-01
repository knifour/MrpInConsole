#ifndef __LTIME_H
#define __LTIME_H

#include <ctime>
#include <string>
#include <iostream>
#include <util.h>

using namespace std;

// 因為系統已有標頭檔time.h，為了避免混淆
// 所以自行設計的時間類別取名LTIME (加L是表示它只處理local time)
class LTIME {
public:
	LTIME();
	LTIME(int, int, int);
	LTIME(const LTIME &);
	string toString () const;
	int getHour(void) const {return mHour;};
	int getMinute(void) const {return mMinute;};
	int getSecond(void) const {return mSecond;};
	int getSeconds(void) const {return mSeconds;};
	
	// 運算子重載
	LTIME operator =(const LTIME source);
	bool operator ==(const LTIME source);
	bool operator >(const LTIME source);
	bool operator <(const LTIME source);
	int  operator -(const LTIME other);
	LTIME operator +(const int day);
	LTIME operator -(const int day);

private:
  // 成員變數
	int mSeconds; 					// 從西元元年年1月1日到現在的天數
	int mHour;
	int mMinute;
	int mSecond;
	
	// 成員函數
  void setHMS(time_t);
	void setSeconds(void) {mSeconds = mHour*3600+mMinute*60+mSecond;};
	void calcSecond(LTIME&, const int);
};

#endif