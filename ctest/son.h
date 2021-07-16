#ifndef __SON_H
#define __SON_H

#include "father.h"

class SON : public FATHER {
protected:
	int mSon;
	
public:
	SON();
	
	void setSon(int) override;
	
	bool operator==(const FATHER& rhs) override;
	FATHER& operator=(const FATHER& rhs) override;
	void printMember() override;
	int getSon() const override;
};

#endif