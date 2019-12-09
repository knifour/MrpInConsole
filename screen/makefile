cc=g++
CFLAGS=-c -std=c++11 -fPIC -D_GNU_SOURCE -I../include
LFLAGS=-L..

test: test.o ../libknifour.a
	$(cc) $(LFLAGS) -o test test.o -lknifour
	
test.o: test.cpp
	$(cc) $(CFLAGS) test.cpp
	
clean:
	rm *.o
