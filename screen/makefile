cc=g++
CFLAGS=-c -std=c++11 -fPIC -D_GNU_SOURCE -I../include
LFLAGS=-L.. -lknifour

test: test.o ../libknifour.a
	$(cc) -o $@ $< $(LFLAGS)
	
test.o: test.cpp
	$(cc) $(CFLAGS) $<
	
clean:
	rm *.o
