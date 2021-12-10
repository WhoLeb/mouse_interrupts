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
	setvect(0x1c, timer);
	printf("*In a robotic voice* tick interrupt has been captured!\n");
	while(getch() != '1')
	{
		gotoxy(1, 2);
		printf("%d", thing);
	}
	setvect(0x1c, oldvec);
}

void interrupt far timer(...)
{
	thing++;
}