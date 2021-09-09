cc=g++
CFLAGS=-c -std=c++11 -D_GNU_SOURCE -I/usr/include/ncursesw -I../include
LFLAGS=-L.. -lknifour

test: test.o  ../libknifour.a
	g++ -o $@ $< $(LFLAGS)
	
test.o: test.cpp
	$(cc) $(CFLAGS) $<
	
clean:
		rm *.o