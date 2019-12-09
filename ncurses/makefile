gc=g++
LFLAGS=-lncursesw -ltinfo
CFLAGS=-c -D_GNU_SOURCE -I/usr/include/ncursesw

hello: hello.o
	$(gc) -o hello hello.o $(LFLAGS)
	
hello.o: hello.cpp
	$(gc) $(CFLAGS) hello.cpp
	
win: win.o
	$(gc) -o win win.o $(LFLAGS)
	
win.o: win.cpp
	$(gc) $(CFLAGS) win.cpp
	
twinkle: twinkle.o
	$(gc) -o twinkle twinkle.o $(LFLAGS)
	
twinkle.o: twinkle.cpp
	$(gc) $(CFLAGS) twinkle.cpp
	
test: test.o
	$(gc) -o test test.o $(LFLAGS)
	
test.o: test.cpp
	$(gc) $(CFLAGS) test.cpp
	
clean:
	rm *.o