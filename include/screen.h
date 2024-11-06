#ifndef SCREEN_H
#define SCREEN_H

// Inicializa a tela e, opcionalmente, desenha bordas ao redor do campo de jogo
void screenInit(int drawBorders);

// Limpa a tela
void screenClear();

// Define um caractere em uma posição específica (x, y)
void screenSetCharAt(int x, int y, char c);

// Move o cursor para a posição (x, y)
void screenGotoxy(int x, int y);

// Atualiza a tela imediatamente
void screenUpdate();

// Esconde o cursor
void screenHideCursor();

// Mostra o cursor
void screenShowCursor();

#endif /* SCREEN_H */
