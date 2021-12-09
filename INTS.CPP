#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void interrupt far timer(...);
void interrupt (far *oldvec)(...);

unsigned long thing = 0;

int main()
{
	clrscr();
	oldvec = getvect(0x1c);
	setvect(0x1c, mouse);
	printf("*In a robotic voice* timer interrupt has been captured!\n");
	while(1)
	{
		if(getch() - '0' == 1) break;
		printf("%d\n", thing);
	}
	setvect(0x1c, oldvec);
}

void interrupt far timer(...)
{
	thing++;
}