#include "screen.h"
#include <stdio.h>

void screenInit(int drawBorders) {
    screenClear();
    screenHideCursor();
    if (drawBorders) {
        for (int x = 0; x < 40; x++) {
            screenSetCharAt(x, 0, '-');
            screenSetCharAt(x, 20, '-');
        }
    }
}

void screenClear() {
    printf("\033[2J\033[H"); // Limpa a tela e move o cursor para o início
}

void screenSetCharAt(int x, int y, char c) {
    screenGotoxy(x, y);
    printf("%c", c);
}

void screenGotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1); // Move o cursor para (x, y)
}

void screenUpdate() {
    fflush(stdout); // Atualiza a tela
}

void screenHideCursor() {
    printf("\033[?25l");
}

void screenShowCursor() {
    printf("\033[?25h");
}
