#ifndef __FATHER_H
#define __FATHER_H

#include <string>

class FATHER {
protected:
	int mBase;
	
public:
	FATHER();
	FATHER(int);
  
	void setBase(int);
	virtual bool operator==(const FATHER& rhs) = 0;
	virtual FATHER& operator=(const FATHER& rhs) = 0;
	virtual void printMember() = 0;
	
	virtual void setSon(int) = 0;
	virtual void setGrandSon(int) = 0;
	int getBase() const;
	virtual int getSon() const = 0;
	virtual int getGrandSon() const = 0;
};

#endif