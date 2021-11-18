cc=g++
CFLAGS=-c -std=c++11 -fPIC -D_GNU_SOURCE
LFLAGS=
OBJS=test.o father.o son.o grandson.o

test: test.o father.o son.o grandson.o
	$(cc) -o $@ $(OBJS) $(LFLAGS)
	
father.o: father.cpp
	$(cc) $(CFLAGS) $<
	
son.o: son.cpp
	$(cc) $(CFLAGS) $<
	
grandson.o: grandson.cpp
	$(cc) $(CFLAGS) $<
	
test.o: test.cpp
	$(cc) $(CFLAGS) $<
	
vector: vector.o
	$(cc) -o $@ $<
	
vector.o: vector.cpp
	$(cc) $(CFLAGS) $<

clean:
	rm *.o