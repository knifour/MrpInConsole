cc=g++
CFLAGS=-c -std=c++11 -D_GNU_SOURCE -I/usr/include/ncursesw -I../include
LFLAGS=-L..

test: test.o  ../libknifour.a
	g++ $(LFLAGS) -o test test.o -lknifour
	
test.o: test.cpp
	$(cc) $(CFLAGS) test.cpp
	
clean:
		rm *.o