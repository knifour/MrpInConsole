cc=g++
dir0:=$(shell pwd)
CFLAGS=-c -std=c++11 -fPIC -D_GNU_SOURCE -I$(dir0)/include
OBJS=util.o schar.o utf8schar.o screen.o twindow.o twmain.o twinmsg.o terminal.o \
mysqlutil.o datetime.o date.o ltime.o utf8.o

libknifour.a: $(OBJS)
	ar rcs libknifour.a $(OBJS)
	
datetime.o: $(dir0)/dtime/datetime.cpp $(dir0)/include/datetime.h
	$(cc) $(CFLAGS) $<
	
date.o: $(dir0)/dtime/date.cpp $(dir0)/include/date.h
	$(cc) $(CFLAGS) $<

ltime.o: $(dir0)/dtime/ltime.cpp $(dir0)/include/ltime.h
	$(cc) $(CFLAGS) $<     
				
util.o: $(dir0)/util/util.cpp $(dir0)/include/util.h
	$(cc) $(CFLAGS) $<
	
utf8.o: $(dir0)/utf8/utf8.cpp $(dir0)/include/utf8.h
	$(cc) $(CFLAGS) $<
        
schar.o: $(dir0)/schar/schar.cpp $(dir0)/include/schar.h
	$(cc) $(CFLAGS) $<
        
utf8schar.o: $(dir0)/schar/utf8schar.cpp $(dir0)/include/schar.h $(dir0)/include/utf8schar.h
	$(cc) $(CFLAGS) $<

terminal.o: $(dir0)/terminal/terminal.cpp $(dir0)/include/terminal.h
	$(cc) $(CFLAGS) $<
        
screen.o: $(dir0)/screen/screen.cpp $(dir0)/include/screen.h
	$(cc) $(CFLAGS) $<
        
twindow.o: $(dir0)/twindow/twindow.cpp $(dir0)/include/twindow.h
	$(cc) $(CFLAGS) $<
	
twmain.o: $(dir0)/twindow/twmain.cpp $(dir0)/include/twmain.h
	$(cc) $(CFLAGS) $<
        
twinmsg.o: $(dir0)/twindow/twinmsg.cpp $(dir0)/include/twinmsg.h
	$(cc) $(CFLAGS) $<
        
mysqlutil.o: $(dir0)/mysql/mysqlutil.cpp $(dir0)/include/mysqlutil.h
	$(cc) $(CFLAGS) $<
        
clean:
	rm *.o
