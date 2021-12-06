#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main(void)
{
    union REGS rg;
    int i;
    unsigned int chosen = 0;
    int nButtons;
    char symbols[] = " .:;+=xX$&";

    // Инициализируем мышь
    rg.x.ax = 0;
    int86(0x33, &rg, &rg);                                                                          // прерывание 0х33 отвечает за мышь

    if (rg.x.bx == 0)
    {
        printf("Mouse not found\n");
        return -1;
    }

    // Включаем курсор
    int cursor = 1;
    rg.x.ax = cursor;
    int86(0x33, &rg, &rg);

    printf("Mouse cursor on. Press any key\n");
    getch();

    clrscr();
    while (!kbhit())                                                                                // проверяет нажата ли клавиатура
    {
        rg.x.ax = 3;                                                                                // тройка отвечает за считывание позиции и нажатых клавиш
        int86(0x33, &rg, &rg);
        gotoxy(1, 1);

        printf("%2d x:%5d y:%5d character:%c ",
               rg.x.bx, rg.x.cx/8, rg.x.dx/8, symbols[chosen % sizeof(symbols)]);
          
        if(rg.x.bx == 0)
            continue;
        if(rg.x.bx == 1)                                                                            //меняет выбранный символ для рисования
            chosen --;
        if(rg.x.bx == 2)
            chosen ++;                                                                              
        if(rg.x.bx == 3)
        {
            rg.x.ax = (++cursor) % 2 + 1;                                                           // включение/выключение курсора
            int86(0x33, &rg, &rg);
        }
        if(rg.x.bx == 4)
        {
            gotoxy(rg.x.cx/8 + 1, rg.x.dx/8 + 1);                                                   // рисование символов
            printf("%c", symbols[chosen % sizeof(symbols)]);
        }
    }
    getch();

    return 0;
}