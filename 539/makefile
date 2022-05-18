cc=g++
CFLAGS=-c -std=c++11 -fPIC -D_GNU_SOURCE -I../include
LFLAGS=-L.. -lknifour

539: 539.o ../libknifour.a
	$(cc) -o $@ $< $(LFLAGS)
	
539.o: 539.cpp
	$(cc) $(CFLAGS) $<
	
b49: b49.o ../libknifour.a
	$(cc) -o $@ $< $(LFLAGS)
	
b49.o: b49.cpp
	$(cc) $(CFLAGS) $<
	
h49: h49.o ../libknifour.a
	$(cc) -o $@ $< $(LFLAGS)
	
h49.o: h49.cpp
	$(cc) $(CFLAGS) $<	
	
clean:
	rm *.o
