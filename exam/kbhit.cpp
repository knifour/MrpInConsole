/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <util.h>
/*#include <stropts.h>*/

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
				initTermios(0);
        initialized = true;
    }
    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

//////////////////////////////////////////////
//    Simple demo of _kbhit()

#include <unistd.h>

int main(int argc, char** argv) {
    printf("Press any key\n");
		fflush(stdout);
    while (! _kbhit()) {
        /*printf(".");
        fflush(stdout);
        usleep(1000);*/
    }
		resetTermios();
		char c=getch();
		printf("你按了%c中斷\n", c);
    printf("\nDone.\n");

    return 0;
} 