cc=g++
CFLAGS=-c -std=c++11 -fPIC -D_GNU_SOURCE -I../include
LFLAGS=-L.. -lknifour

539: 539.o ../libknifour.a
	$(cc) -o $@ $< $(LFLAGS)
	
539.o: 539.cpp
	$(cc) $(CFLAGS) $<
	
clean:
	rm *.o
