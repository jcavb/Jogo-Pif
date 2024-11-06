#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define LARGURA 3         // Número de faixas (esquerda, meio, direita)
#define ALTURA 20         // Altura da pista
#define CARRO_CHAR 'A'    // Carro do jogador
#define OBSTACULO_CHAR '#'// Obstáculo
#define INTERVALO_TEMPO 100 // Intervalo de tempo para atualizar o jogo em ms

typedef struct {
    int x, y;
} Posicao;

// Variáveis globais
Posicao carro;
Posicao obstaculos[ALTURA]; // Obstáculos ao longo da pista
int pontuacao = 0;          // Pontuação do jogador
int jogoAtivo = 1;          // Estado do jogo (1 = ativo, 0 = game over)

// Função para inicializar o jogo
void inicializarJogo() {
    screenInit(1);          // Inicia a tela com bordas
    keyboardInit();         // Inicia o teclado
    timerInit(INTERVALO_TEMPO); // Inicia o timer com intervalo de 100ms
    srand(time(NULL));      // Semente para geração aleatória

    // Configura a posição inicial do carro na faixa do meio
    carro.x = LARGURA / 2;
    carro.y = ALTURA - 2;

    // Inicializa os obstáculos fora da tela
    for (int i = 0; i < ALTURA; i++) {
        obstaculos[i].x = rand() % LARGURA; // Gera obstáculos em faixas aleatórias
        obstaculos[i].y = -1;               // Obstáculo começa fora da tela
    }
}

// Função para desenhar o carro e os obstáculos
void desenhar() {
    screenClear();

    // Desenha o carro
    screenSetCharAt(carro.x, carro.y, CARRO_CHAR);

    // Desenha os obstáculos
    for (int i = 0; i < ALTURA; i++) {
        if (obstaculos[i].y >= 0) { // Desenha somente se o obstáculo está na pista
            screenSetCharAt(obstaculos[i].x, obstaculos[i].y, OBSTACULO_CHAR);
        }
    }

    // Exibe a pontuação
    screenGotoxy(0, ALTURA + 1);
    printf("Pontuação: %d\n", pontuacao);
    screenUpdate();
}

// Função para atualizar a posição dos obstáculos
void atualizarObstaculos() {
    int faixa_ocupada[3] = {0, 0, 0}; // Controle de quais faixas têm obstáculos

    for (int i = 0; i < ALTURA; i++) {
        if (obstaculos[i].y >= 0) {
            obstaculos[i].y++; // Move o obstáculo para baixo

            // Verifica colisão com o carro
            if (obstaculos[i].x == carro.x && obstaculos[i].y == carro.y) {
                jogoAtivo = 0; // Game over
            }
        } else {
            // Gera um novo obstáculo aleatório no topo, garantindo no máximo 2 faixas ocupadas
            int nova_faixa;
            do {
                nova_faixa = rand() % LARGURA;
            } while (faixa_ocupada[0] + faixa_ocupada[1] + faixa_ocupada[2] >= 2 && faixa_ocupada[nova_faixa] == 1);

            obstaculos[i].x = nova_faixa;
            obstaculos[i].y = 0;
            faixa_ocupada[nova_faixa] = 1;
        }

        // Remove o obstáculo se sair da tela
        if (obstaculos[i].y >= ALTURA) {
            obstaculos[i].y = -1; // Sai da tela
            pontuacao++;          // Aumenta a pontuação ao desviar
        }
    }
}


// Função para controlar o carro
void controlarCarro(int tecla) {
    switch (tecla) {
        case 'w': if (carro.y > 0) carro.y--; break;             // Move para cima
        case 's': if (carro.y < ALTURA - 1) carro.y++; break;    // Move para baixo
        case 'a': if (carro.x > 0) carro.x--; break;             // Move para a faixa da esquerda
        case 'd': if (carro.x < LARGURA - 1) carro.x++; break;   // Move para a faixa da direita
    }
}

// Função principal do jogo
int main() {
    inicializarJogo();

    while (jogoAtivo) {
        desenhar();
        
        // Aguarda a entrada do jogador antes de cada atualização
        int tecla = readch();
        controlarCarro(tecla);
        
        atualizarObstaculos(); // Atualiza a posição dos obstáculos
    }

    // Exibe mensagem de fim de jogo
    screenClear();
    screenGotoxy(0, ALTURA / 2);
    printf("Game Over! Pontuação final: %d\n", pontuacao);

    return 0;
}
