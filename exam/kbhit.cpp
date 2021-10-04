/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <util.h>
/*#include <stropts.h>*/

#include <unistd.h>

int main(int argc, char** argv) {
	  int b;
		unsigned char c[5];
		
    printf("Press any key\n");
		fflush(stdout);
    while (!(b=_kbhit())) {
        /*printf(".");
        fflush(stdout);
        usleep(1000);*/
    }
		resetTermios();
		switch(b){
		case 1:
		  c[0] = getch();
			if (c[0]==127||c[0]<32)
				printf("特殊按鍵，代號%d\n", c[0]);
		  else
				printf("%c", c[0]);
			break;
		case 2:
		  c[0] = getch();
			c[1] = getch();
			printf("%x, %x", c[0], c[1]);
			break;
		case 3:
		  c[0] = getch();
			c[1] = getch();
			c[2] = getch();
			printf("%x %x %x", c[0], c[1], c[2]);
			break;
		case 4:
		  c[0] = getch();
			c[1] = getch();
			c[2] = getch();
			c[3] = getch();
			printf("%x %x %x %x", c[0], c[1], c[2], c[3]);
			break;
		};

    return 0;
} 