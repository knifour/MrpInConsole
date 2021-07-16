#ifndef __SON_H
#define __SON_H

#include "father.h"

class SON : public FATHER {
protected:
	int mSon;
	
public:
	SON();
	
	void setValue(int);
	
	bool operator==(const SON& rhs);
	void printMember();
};

#endif