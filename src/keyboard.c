#include "keyboard.h"
#include <stdio.h>

void keyboardInit() {}

void keyboardDestroy() {}

int keyhit() {
    return 1; // Sempre retorna 1, já que não podemos detectar teclas sem bloqueio sem <termios.h>
}

int readch() {
    return getchar();
}
