#include <tptime.h>

TPTIME::TPTIME(){
	time_t Origin = time(NULL) + 28800; // 加28800是把GMT時間調整成台北時間
	
	setHMS(Origin);
}

TPTIME::TPTIME(int hour, int minute, int second){
	if (hour < 0 || hour > 23) 
		mHour = 0;
	else
		mHour = hour;
	
	if (minute < 0 || minute > 59)
		mMinute = 0;
	else
		mMinute = minute;
	
	if (second < 0 || minute > 59)
		mSecond = 0;
	else
		mSecond = second;
	
	setSeconds();
}

TPTIME::TPTIME(const TPTIME& source){
	mSeconds = source.mSeconds;
	mHour = source.mHour;
	mMinute = source.mMinute;
	mSecond = source.mSecond;
}

string TPTIME::toString(void) const{
	char buf[20];
	
	sprintf(buf, "%02d:%02d:%02d", mHour, mMinute, mSecond);
	
	return string(buf);
}

void TPTIME::setHMS(time_t Origin){
	int secs = Origin % 86400;
	
	mSeconds = secs;
	
	mHour = secs / 3600;
	secs = secs % 3600;
	
	mMinute = secs / 60;
	mSecond = secs % 60;
}

TPTIME TPTIME::operator =(const TPTIME source){
	mSeconds = source.mSeconds;
	mHour = source.mHour;
	mMinute = source.mMinute;
	mSecond = source.mSecond;
	
	return *this;
}

bool TPTIME::operator ==(const TPTIME source){
	if (mSeconds == source.mSeconds)
		return true;
	else
		return false;
}

bool TPTIME::operator >(const TPTIME source){
	if (mSeconds > source.mSeconds)
		return true;
	else
		return false;
}

bool TPTIME::operator <(const TPTIME source){
	if (mSeconds < source.mSeconds)
		return true;
	else
		return false;
}

int TPTIME::operator -(const TPTIME other){
	return (mSeconds - other.mSeconds);
}

TPTIME TPTIME::operator +(const int second){
	TPTIME temp(*this);
	int ts = temp.mSecond + second;
	
	calcSecond(temp, ts);
	
	return temp;
}

TPTIME TPTIME::operator -(const int second){
	TPTIME temp(*this);
	int ts = temp.mSecond - second;
	
	calcSecond(temp, ts);
	
	return temp;
}

void TPTIME::calcSecond(TPTIME& temp, const int second){
	int ts = second;
	
	if (ts >= 0){
		while (ts >= 60){
			temp.mMinute++;
			ts = ts - 60;
		}
		while (temp.mMinute >= 60){
			temp.mHour++;
			temp.mMinute = temp.mMinute - 60;
		}
		while (temp.mHour > 23)
			temp.mHour -= 24;
	} else {
		while (ts < 0){
			temp.mMinute--;
			ts = ts + 60;
		}
		while (temp.mMinute < 0){
			temp.mHour--;
			temp.mMinute = temp.mMinute - 60;
		}
		while (temp.mHour < 0)
	    temp.mHour += 24;
	}
	temp.mSecond = ts;
	temp.setSeconds();
}