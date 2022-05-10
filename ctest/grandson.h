#ifndef __GRANDSON_H
#define __GRANDSON_H

#include "son.h"

class GRANDSON : public SON {
protected:
	int mGrandSon;
	
public:
	GRANDSON();
	
	void setGrandSon(int) override;
	
	bool operator==(const FATHER& rhs) override;
	FATHER& operator=(const FATHER& rhs) override;
	void printMember() override;
	int getGrandSon() const override;
};

#endif