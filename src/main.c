#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define LARGURA 40 // Largura do campo
#define ALTURA 20 // Altura do campo
#define SNAKE_MAX_LENGTH 100

// Estrutura para representar posições
typedef struct {
    int x, y;
} Posicao;

// Variáveis globais
Posicao cobra[SNAKE_MAX_LENGTH];
int comprimento = 3; // Tamanho inicial da cobra
int direcaoX = 1, direcaoY = 0; // Direção inicial para a direita
Posicao comida;

// Função para inicializar o jogo
void inicializarJogo() {
    screenInit(1);
    keyboardInit();
    timerInit(100);

    srand(time(NULL));
    // Inicializa a cobra no centro do campo
    for (int i = 0; i < comprimento; i++) {
        cobra[i].x = LARGURA / 2 - i;
        cobra[i].y = ALTURA / 2;
    }
    // Gera a primeira comida
    comida.x = rand() % LARGURA;
    comida.y = rand() % ALTURA;
}

// Função para encerrar o jogo
void encerrarJogo() {
    screenClear();
    printf("Fim de Jogo! Pontuação: %d\n", comprimento - 3);
}

// Função para desenhar a cobra e a comida
void desenhar() {
    screenClear();
    screenSetCharAt(comida.x, comida.y, 'O'); // Desenha a comida
    for (int i = 0; i < comprimento; i++) {
        screenSetCharAt(cobra[i].x, cobra[i].y, '#'); // Desenha cada parte da cobra
    }
}

// Função para atualizar a posição da cobra
void atualizarPosicao() {
    // Move o corpo da cobra
    for (int i = comprimento - 1; i > 0; i--) {
        cobra[i] = cobra[i - 1];
    }
    // Atualiza a posição da cabeça
    cobra[0].x += direcaoX;
    cobra[0].y += direcaoY;

    // Verifica se a cobra comeu a comida
    if (cobra[0].x == comida.x && cobra[0].y == comida.y) {
        comprimento++;
        comida.x = rand() % LARGURA;
        comida.y = rand() % ALTURA;
    }

    // Verifica colisão com as bordas
    if (cobra[0].x < 0 || cobra[0].x >= LARGURA || cobra[0].y < 0 || cobra[0].y >= ALTURA) {
        encerrarJogo();
        exit(0);
    }

    // Verifica colisão com o próprio corpo
    for (int i = 1; i < comprimento; i++) {
        if (cobra[0].x == cobra[i].x && cobra[0].y == cobra[i].y) {
            encerrarJogo();
            exit(0);
        }
    }
}

// Função para controlar a direção da cobra
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
        timerSleep(100); // Controle da velocidade

        if (keyboardHit()) { // Verifica se uma tecla foi pressionada
            int tecla = keyboardRead();
            controlarDirecao(tecla);
        }

        atualizarPosicao();
    }

    encerrarJogo();
    return 0;
}
