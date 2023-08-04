cc=g++
CFLAGS=-c -std=c++11 -fPIC -D_GNU_SOURCE -I../include
LFLAGS=-L.. -lknifour

menu: menu.o ../libknifour.a
	$(cc) -o $@ $< $(LFLAGS)
	
menu.o: menu.cpp
	$(cc) $(CFLAGS) $<
	
form: form.o
	$(cc) -o $@ $<
	
form.o: form.cpp
	$(cc) $(CFLAGS) $<
	
clean:
	rm *.o
