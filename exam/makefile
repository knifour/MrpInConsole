cc=g++
CFLAGS=-c -std=c++11 -fPIC -D_GNU_SOURCE -I../include
LFLAGS=-L..

test: test.o
	$(cc) $(LFLAGS) -o test test.o -lknifour
	
test.o: test.cpp
	$(cc) $(CFLAGS) test.cpp
	
keypad: keypad.o
	$(cc) $(LFLAGS) -o keypad keypad.o -lknifour
	
keypad.o: keypad.cpp
	$(cc) $(CFLAGS) keypad.cpp
	
comp: comp.o
	$(cc) $(LFLAGS) -o comp comp.o
	
comp.o: comp.cpp
	$(cc) $(CFLAGS) comp.cpp
	
cheat: cheat.o
	$(cc) $(LFLAGS) -o cheat cheat.o
	
cheat.o: cheat.cpp
	$(cc) $(CFLAGS) cheat.cpp

args: args.o
	$(cc) $(LFLAGS) -o args args.o
	
args.o: args.cpp
	$(cc) $(CFLAGS) args.cpp
	
inkey: inkey.o
	$(cc) $(LFLAGS) -o inkey inkey.cpp
	
inkey.o: inkey.cpp
	$(cc) $(CFLAGS) inkey.cpp
	
search: search.o
	$(cc) $(LFLAGS) -o search search.o
	
search.o: search.cpp
	$(cc) $(CFLAGS) search.cpp
	
modify: modify.o
	$(cc) $(LFLAGS) -o modify modify.o
	
modify.o: modify.cpp
	$(cc) $(CFLAGS) modify.cpp 
	
nnpra: nnpra.o
	$(cc) $(LFLAGS) -o nnpra nnpra.o

nnpra.o: nnpra.cpp nnpra.h
	$(cc) $(CFLAGS) nnpra.cpp
 
clean:
	rm *.o
