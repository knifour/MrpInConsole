cc=g++
CFLAGS=-c -std=c++11 -fPIC -D_GNU_SOURCE
LFLAGS=-L..

father.o: father.cpp
	$(cc) $(CFLAGS) father.cpp
	
son.o: son.cpp
	$(cc) $(CFLAGS) son.cpp	
	
test.o: test.cpp
	$(cc) $(CFLAGS) test.cpp

test: test.o father.o son.o
	$(cc) $(LFLAGS) -o test test.o father.o son.o
	
clean:
	rm *.o