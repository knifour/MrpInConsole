cc=g++
CFLAGS=-c -std=c++11 -fPIC -D_GNU_SOURCE -I../include
LFLAGS=-L.. -lknifour

test: test.o ../libknifour.a
	$(cc) $(LFLAGS) -o $@ $<
	
test.o: test.cpp
	$(cc) $(CFLAGS) $<
	
schar.o: schar.cpp
	$(cc) $(CFLAGS) $<

utf8schar.o: utf8schar.cpp
	$(cc) $(CFLAGS) $<
	
clean:
	rm *.o
