cc=g++
imysql:=$(shell mysql_config --include)
lmysql:=$(shell mysql_config --libs)
CFLAGS=$(imysql) -I../include
LFLAGS=-L.. -lknifour $(lmysql)

myhello: myhello.o ../libknifour.a
	$(cc) -o $@ $< $(LFLAGS)
	
myhello.o: myhello.cpp
	$(cc) $(CFLAGS) -c $<
	
clean:
	rm myhello
	rm *.o