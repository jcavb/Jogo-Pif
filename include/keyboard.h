#ifndef KEYBOARD_H
#define KEYBOARD_H

// Inicializa o teclado (não faz nada especial aqui, mas está para manter a consistência)
void keyboardInit();

// Libera recursos do teclado (não faz nada especial aqui, mas está para manter a consistência)
void keyboardDestroy();

// Retorna 1 sempre, já que sem <termios.h> não há como verificar teclas sem bloqueio
int keyhit();

// Lê um caractere da entrada
int readch();

#endif /* KEYBOARD_H */
