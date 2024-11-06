/**
 * screen.c
 * Criado em 23 de agosto de 2023
 * Autor: Tiago Barros
 * Baseado no curso "De C para C++ - 2002"
 */

#include "screen.h"
#include <stdio.h>

// Função que retorna um caractere na posição (x, y) - placeholder
char screenGetCharAt(int x, int y) {
    // Por enquanto, retornamos um espaço em branco
    return ' ';
}

// Função para desenhar bordas ao redor da tela
void screenDrawBorders() {
    char hbc = BOX_HLINE;  // Caracter horizontal da borda
    char vbc = BOX_VLINE;  // Caracter vertical da borda

    screenClear();
    screenBoxEnable();  // Ativa os caracteres de borda

    // Canto superior esquerdo
    screenGotoxy(MINX, MINY);
    printf("%c", BOX_UPLEFT);

    // Linha superior
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MINY);
        printf("%c", hbc);
    }

    // Canto superior direito
    screenGotoxy(MAXX, MINY);
    printf("%c", BOX_UPRIGHT);

    // Linhas laterais esquerda e direita
    for (int i = MINY + 1; i < MAXY; i++) {
        screenGotoxy(MINX, i);
        printf("%c", vbc);
        screenGotoxy(MAXX, i);
        printf("%c", vbc);
    }

    // Canto inferior esquerdo
    screenGotoxy(MINX, MAXY);
    printf("%c", BOX_DWNLEFT);

    // Linha inferior
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MAXY);
        printf("%c", hbc);
    }

    // Canto inferior direito
    screenGotoxy(MAXX, MAXY);
    printf("%c", BOX_DWNRIGHT);

    screenBoxDisable();  // Desativa os caracteres de borda
}

// Função para inicializar a tela
void screenInit(int drawBorders) {
    screenClear();       // Limpa a tela
    screenHideCursor();  // Esconde o cursor
    if (drawBorders) {
        screenDrawBorders(); // Desenha as bordas se drawBorders for diferente de zero
    }
}

// Função para destruir a tela e restaurar as configurações iniciais
void screenDestroy() {
    printf("%s[0;39;49m", ESC); // Resetar as cores
    screenSetNormal();
    screenClear();
    screenHomeCursor();
    screenShowCursor();
}

// Função para mover o cursor para uma posição (x, y)
void screenGotoxy(int x, int y) {
    x = (x < 0 ? 0 : x >= MAXX ? MAXX - 1 : x);
    y = (y < 0 ? 0 : y >= MAXY ? MAXY - 1 : y); // Corrigido para MAXY - 1

    printf("%s[f%s[%dB%s[%dC", ESC, ESC, y, ESC, x);
}

// Função para definir a cor do texto
void screenSetTextColor(int color) {
    switch(color) {
        case COLOR_GREEN:
            printf("\033[32m");
            break;
        case COLOR_YELLOW:
            printf("\033[33m");
            break;
        case COLOR_DEFAULT:
        default:
            printf("\033[0m");
            break;
    }   
}

// Função para resetar a cor do texto para o padrão
void screenResetTextColor() {
    printf("\033[0m"); 
}

// Função para definir as cores de primeiro e segundo plano
void screenSetColor(screenColor fg, screenColor bg) {
    char atr[] = "[0;";

    // Se a cor do primeiro plano for maior que LIGHTGRAY, define negrito
    if (fg > LIGHTGRAY) {
        atr[1] = '1';
        fg -= 8;
    }

    printf("%s%s%d;%dm", ESC, atr, fg + 30, bg + 40);
}

// Função para definir um caractere em uma posição específica
void screenSetCharAt(int x, int y, char c) {
    screenGotoxy(x, y); // Move o cursor para (x, y)
    printf("%c", c);    // Exibe o caractere 'c' na posição especificada
    screenUpdate();     // Atualiza a tela imediatamente
}
