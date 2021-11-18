#ifndef __TWMSGBOX_H
#define __TWMSGBOX_H

#include <twindow.h>
#include <tableset.h>

template <class T>
class TWMSGBOX : public TWINDOW<T>{
private:

protected:

public:
  TWMSGBOX();
  TWMSGBOX(TWINDOW<T>*, const char *, WIN);
	~TWMSGBOX();
};

#endif