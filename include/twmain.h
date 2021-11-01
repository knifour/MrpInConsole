#ifndef __TWMAIN_H
#define __TWMAIN_H

#include <twindow.h>

template <class T>
class TWMAIN : public TWINDOW<T> {
private:

protected:

public:
  TWMAIN(TERMINAL<T>*);
	~TWMAIN();
};

#endif