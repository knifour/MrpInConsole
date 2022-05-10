#ifndef __TWMAIN_H
#define __TWMAIN_H

#include <twindow.h>
#include <tableset.h>

template <class T>
class TWMAIN : public TWINDOW<T>{
private:

protected:

public:
  TWMAIN();
  TWMAIN(TERMINAL<T>*);
	~TWMAIN();
};

#endif