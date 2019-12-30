cc=g++
CFLAGS=-c -std=c++11 -fPIC -D_GNU_SOURCE -I../include
LFLAGS=-L..

test: test.o
	$(cc) $(LFLAGS) -o test test.o -lknifour -ltermcap
	
test.o: test.cpp
	$(cc) $(CFLAGS) test.cpp
	
keypad: keypad.o
	$(cc) $(LFLAGS) -o keypad keypad.o -lknifour
	
keypad.o: keypad.cpp
	$(cc) $(CFLAGS) keypad.cpp
	
clean:
	rm *.o
