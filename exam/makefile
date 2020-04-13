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
	
search: search.o
	$(cc) $(LFLAGS) -o search search.o
	
search.o: search.cpp
	$(cc) $(CFLAGS) search.cpp
	
modify: modify.o
	$(cc) $(LFLAGS) -o modify modify.o
	
modify.o: modify.cpp
	$(cc) $(CFLAGS) modify.cpp 
 
clean:
	rm *.o
