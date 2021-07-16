#ifndef __FATHER_H
#define __FATHER_H

#include <string>

class FATHER {
protected:
	int mBase;
	
public:
	FATHER();
  
	void setValue(int);
	bool operator==(const FATHER& rhs);
	void printMember();
};

#endif