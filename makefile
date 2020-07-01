cc=g++
dir0:=$(shell pwd)
CFLAGS=-c -std=c++11 -fPIC -D_GNU_SOURCE -I$(dir0)/include
OBJS=util.o schar.o utf8schar.o screen.o twindow.o twinmsg.o mysqlutil.o \
datetime.o date.o ltime.o

libknifour.a: $(OBJS)
	ar rcs libknifour.a $(OBJS)
	
datetime.o: $(dir0)/dtime/datetime.cpp $(dir0)/include/datetime.h
	$(cc) $(CFLAGS) $(dir0)/dtime/datetime.cpp
	
date.o: $(dir0)/dtime/date.cpp $(dir0)/include/date.h
	$(cc) $(CFLAGS) $(dir0)/dtime/date.cpp

ltime.o: $(dir0)/dtime/ltime.cpp $(dir0)/include/ltime.h
	$(cc) $(CFLAGS) $(dir0)/dtime/ltime.cpp        
				
util.o: $(dir0)/util/util.cpp $(dir0)/include/util.h
	$(cc) $(CFLAGS) $(dir0)/util/util.cpp
        
schar.o: $(dir0)/schar/schar.cpp $(dir0)/include/schar.h
	$(cc) $(CFLAGS) $(dir0)/schar/schar.cpp
        
utf8schar.o: $(dir0)/schar/utf8schar.cpp $(dir0)/include/utf8schar.h
	$(cc) $(CFLAGS) $(dir0)/schar/utf8schar.cpp     
        
screen.o: $(dir0)/screen/screen.cpp $(dir0)/include/screen.h
	$(cc) $(CFLAGS) $(dir0)/screen/screen.cpp
        
twindow.o: $(dir0)/twindow/twindow.cpp $(dir0)/include/twindow.h
	$(cc) $(CFLAGS) $(dir0)/twindow/twindow.cpp
        
twinmsg.o: $(dir0)/twindow/twinmsg.cpp $(dir0)/include/twinmsg.h
	$(cc) $(CFLAGS) $(dir0)/twindow/twinmsg.cpp
        
mysqlutil.o: $(dir0)/mysql/mysqlutil.cpp $(dir0)/include/mysqlutil.h
	$(cc) $(CFLAGS) $(dir0)/mysql/mysqlutil.cpp
        
clean:
	rm *.o
