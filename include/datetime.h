#ifndef __DATETIME_H
#define __DATETIME_H

#include <ctime>
#include <string>
#include <iostream>
#include <stdint.h>
#include <util.h>

using namespace std;

enum DATETYPE: int{ /* 需增加編譯條件 -std=c++11 才可以正常編譯 */
	ADSLASH   =  0,
	AD        =  1,
	MINGSLASH =  2,
	MING      =  3
};

#define OLDDAYS 719163  // 到1970年1月1日的天數(西元元年1月1日算第1天)

class DATETIME {
public:
	DATETIME();
	DATETIME(int, int, int);
	DATETIME(int, int, int, int, int, int);
	string getDateString (int) const;
	string getTimeString (void) const;
	int getYear(void) const {return mYear;};
	int getMonth(void) const {return mMonth;};
	int getDay(void) const {return mDay;};
	int getHour(void) const {return mHour;};
	int getMinute(void) const {return mMinute;};
	int getSecond(void) const {return mSecond;};
	int getDayOfWeek(void) const {return (mOrigin/86400+4)%7;};
	
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
  void setYMD(void);
  void setHMS(void);
	void setOrigin(void);
};

#endif