#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define LARGURA 79
#define ALTURA 25
#define SNAKE_MAX_LENGTH 100

typedef struct {
    int x, y;
} Posicao;

Posicao cobra[SNAKE_MAX_LENGTH];
int comprimento = 3;
int direcaoX = 1, direcaoY = 0;
Posicao comida;

void inicializarJogo() {
    screenInit(1);
    keyboardInit();
    timerInit(100);

    srand(time(NULL));

    for (int i = 0; i < comprimento; i++) {
        cobra[i].x = LARGURA / 2 - i;
        cobra[i].y = ALTURA / 2;
    }

    // Inicializa a comida dentro do campo, mas fora das bordas
    comida.x = 1 + rand() % (LARGURA - 2); // Garante que está entre 1 e LARGURA - 2
    comida.y = 1 + rand() % (ALTURA - 2);  // Garante que está entre 1 e ALTURA - 2
}

void encerrarJogo() {
    screenClear();
    printf("Fim de Jogo! Pontuação: %d\n", comprimento - 3);
}

void desenhar() {
    screenClear();
    screenSetCharAt(comida.x, comida.y, 'O');
    for (int i = 0; i < comprimento; i++) {
        screenSetCharAt(cobra[i].x, cobra[i].y, '#');
    }
}

void atualizarPosicao() {
    // Move o corpo da cobra
    for (int i = comprimento - 1; i > 0; i--) {
        cobra[i] = cobra[i - 1];
    }

    // Atualiza a posição da cabeça
    cobra[0].x += direcaoX;
    cobra[0].y += direcaoY;

    // Colisão com as bordas
    if (cobra[0].x < 0 || cobra[0].x >= LARGURA || cobra[0].y < 0 || cobra[0].y >= ALTURA) {
        encerrarJogo();
        exit(0);
    }

    // Colisão com o próprio corpo
    for (int i = 1; i < comprimento; i++) {
        if (cobra[0].x == cobra[i].x && cobra[0].y == cobra[i].y) {
            encerrarJogo();
            exit(0);
        }
    }

    // Verifica se comeu a comida
    if (cobra[0].x == comida.x && cobra[0].y == comida.y) {
        comprimento++;
        // Gera uma nova posição para a comida dentro das bordas
        comida.x = 1 + rand() % (LARGURA - 2); // Entre 1 e LARGURA - 2
        comida.y = 1 + rand() % (ALTURA - 2);  // Entre 1 e ALTURA - 2
    }
}

void controlarDirecao(int tecla) {
    if (tecla == 'w' && direcaoY == 0) { direcaoX = 0; direcaoY = -1; }
    if (tecla == 's' && direcaoY == 0) { direcaoX = 0; direcaoY = 1; }
    if (tecla == 'a' && direcaoX == 0) { direcaoX = -1; direcaoY = 0; }
    if (tecla == 'd' && direcaoX == 0) { direcaoX = 1; direcaoY = 0; }
}

int main() {
    inicializarJogo();

    while (1) {
        desenhar();
        timerSleep(100);

        if (keyhit()) {
            int tecla = readch();
            controlarDirecao(tecla);
        }

        atualizarPosicao();
    }

    encerrarJogo();
    return 0;
}
