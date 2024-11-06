#include "screen.h"
#include <stdio.h>

// Inicializa a tela e, opcionalmente, desenha bordas
void screenInit(int drawBorders) {
    screenClear();
    screenHideCursor();
    
    if (drawBorders) {
        // Desenha bordas simples ao redor do campo de jogo
        for (int x = 0; x < 40; x++) {
            screenSetCharAt(x, 0, '-');        // Linha superior
            screenSetCharAt(x, 20, '-');       // Linha inferior
        }
        for (int y = 0; y <= 20; y++) {
            screenSetCharAt(0, y, '|');        // Borda esquerda
            screenSetCharAt(39, y, '|');       // Borda direita
        }
    }
}

// Limpa a tela
void screenClear() {
    printf("\033[2J\033[H"); // Comando ANSI para limpar a tela e mover o cursor para o início
}

// Define um caractere em uma posição específica (x, y)
void screenSetCharAt(int x, int y, char c) {
    screenGotoxy(x, y);
    printf("%c", c);
}

// Move o cursor para a posição (x, y)
void screenGotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1); // Comando ANSI para mover o cursor
}

// Atualiza a tela imediatamente (no caso de algum buffer de saída)
void screenUpdate() {
    fflush(stdout); // Garante que tudo foi impresso na tela
}

// Esconde o cursor
void screenHideCursor() {
    printf("\033[?25l");
}

// Mostra o cursor
void screenShowCursor() {
    printf("\033[?25h");
}
