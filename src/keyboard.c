#include "keyboard.h"
#include <stdio.h>

void keyboardInit() {
    // Inicialização simples, sem configurações especiais
}

void keyboardDestroy() {
    // Limpeza simples, sem configurações especiais
}

// Função para verificar se uma tecla foi pressionada (com getchar)
int keyhit() {
    return 1;  // Sempre retorna 1, pois sem <termios.h> não é possível fazer verificações sem bloqueio
}

// Função para ler um caractere da entrada
int readch() {
    return getchar(); // Aguarda até que uma tecla seja pressionada
}
