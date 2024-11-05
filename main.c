#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define SNAKE_MAX_LENGTH 100 // Define o comprimento máximo da cobra
#define FOOD_SYMBOL '$' // Define o símbolo do alimento
#define SNAKE_SYMBOL '*' // Define o símbolo da cobra
#define HORIZONTAL_BORDER_SYMBOL '-' // Define o símbolo da borda horizontal
#define VERTICAL_BORDER_SYMBOL '|' // Define o símbolo da borda vertical
#define SAVE_FILE "snake_save.txt" // Nome do arquivo de salvamento

// Constantes para a área de jogo
#define MINX 0
#define MAXX 79
#define MINY 0
#define MAXY 23

typedef struct {
    int x;
    int y;
} Posicao;

typedef enum {
    CIMA,
    BAIXO,
    ESQUERDA,
    DIREITA
} Direcao;

typedef struct {
    Posicao *corpo;
    int comprimento;
    Direcao direcao;
} Cobra;

Cobra cobra;
Posicao posicaoComida;
int pontuacao = 0;
int intervaloTimer = 150;

void inicializarCobra() {
    cobra.corpo = (Posicao *)malloc(SNAKE_MAX_LENGTH * sizeof(Posicao));
    if (cobra.corpo == NULL) {
        printf("Erro ao alocar memória para a cobra.\n");
        exit(1);
    }
    cobra.corpo[0].x = MAXX / 2;
    cobra.corpo[0].y = MAXY / 2;
    cobra.comprimento = 1;
    cobra.direcao = DIREITA;
}

void destruirCobra() {
    if (cobra.corpo != NULL) {
        free(cobra.corpo);
        cobra.corpo = NULL;
    }
}

void moverCobra() {
    for (int i = cobra.comprimento - 1; i > 0; i--) {
        cobra.corpo[i] = cobra.corpo[i - 1];
    }
    switch (cobra.direcao) {
        case CIMA: cobra.corpo[0].y--; break;
        case BAIXO: cobra.corpo[0].y++; break;
        case ESQUERDA: cobra.corpo[0].x--; break;
        case DIREITA: cobra.corpo[0].x++; break;
    }
}

int verificarColisao() {
    if (cobra.corpo[0].x <= MINX || cobra.corpo[0].x >= MAXX || cobra.corpo[0].y <= MINY || cobra.corpo[0].y >= MAXY) {
        return 1;
    }
    for (int i = 1; i < cobra.comprimento; i++) {
        if (cobra.corpo[0].x == cobra.corpo[i].x && cobra.corpo[0].y == cobra.corpo[i].y) {
            return 1;
        }
    }
    return 0;
}

void gerarComida() {
    do {
        posicaoComida.x = (rand() % (MAXX - MINX - 1)) + MINX + 1;
        posicaoComida.y = (rand() % (MAXY - MINY - 1)) + MINY + 1;
    } while (screenGetCharAt(posicaoComida.x, posicaoComida.y) != ' ');
}

int verificarComida() {
    if (cobra.corpo[0].x == posicaoComida.x && cobra.corpo[0].y == posicaoComida.y) {
        pontuacao++;
        cobra.comprimento++;
        gerarComida();
        if (intervaloTimer > 50) {
            intervaloTimer -= 10;
        }
        timerDestroy();
        timerInit(intervaloTimer);
        return 1;
    }
    return 0;
}

void desenharCobra() {
    screenSetTextColor(COLOR_GREEN);
    for (int i = 0; i < cobra.comprimento; i++) {
        screenGotoxy(cobra.corpo[i].x, cobra.corpo[i].y);
        printf("%c", SNAKE_SYMBOL);
    }
    screenResetTextColor();
}

void desenharComida() {
    screenSetTextColor(COLOR_YELLOW);
    screenGotoxy(posicaoComida.x, posicaoComida.y);
    printf("%c", FOOD_SYMBOL);
    screenResetTextColor();
}

void desenharBorda() {
    for (int x = MINX; x <= MAXX; x++) {
        screenGotoxy(x, MINY);
        printf("%c", HORIZONTAL_BORDER_SYMBOL);
        screenGotoxy(x, MAXY);
        printf("%c", HORIZONTAL_BORDER_SYMBOL);
    }
    for (int y = MINY + 1; y < MAXY; y++) {
        screenGotoxy(MINX, y);
        printf("%c", VERTICAL_BORDER_SYMBOL);
        screenGotoxy(MAXX, y);
        printf("%c", VERTICAL_BORDER_SYMBOL);
    }
}

void desenharPontuacao() {
    screenGotoxy(MAXX - 20, MAXY + 1);
    printf("Dinheiro acumulado: %d", pontuacao);
}

void salvarJogo() {
    FILE *file = fopen(SAVE_FILE, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de salvamento.\n");
        return;
    }
    fprintf(file, "%d %d %d %d %d %d %d %d\n", cobra.comprimento, cobra.direcao, cobra.corpo[0].x, cobra.corpo[0].y, posicaoComida.x, posicaoComida.y, pontuacao, intervaloTimer);
    fclose(file);
}

void carregarJogo() {
    FILE *file = fopen(SAVE_FILE, "r");
    if (file == NULL) {
        printf("Nenhum arquivo de salvamento encontrado.\n");
        return;
    }
    fscanf(file, "%d %d %d %d %d %d %d %d", &cobra.comprimento, &cobra.direcao, &cobra.corpo[0].x, &cobra.corpo[0].y, &posicaoComida.x, &posicaoComida.y, &pontuacao, &intervaloTimer);
    fclose(file);
}

int main() {
    srand(time(NULL));
    screenInit(1);
    keyboardInit();
    timerInit(intervaloTimer);

    printf("Deseja carregar o jogo anterior? (s/n): ");
    char escolha;
    scanf(" %c", &escolha);
    if (escolha == 's' || escolha == 'S') {
        carregarJogo();
    } else {
        inicializarCobra();
        gerarComida();
    }

    while (1) {
        if (keyhit()) {
            int tecla = readch();
            switch (tecla) {
                case 'w': case 'W': if (cobra.direcao != BAIXO) cobra.direcao = CIMA; break;
                case 's': case 'S': if (cobra.direcao != CIMA) cobra.direcao = BAIXO; break;
                case 'a': case 'A': if (cobra.direcao != DIREITA) cobra.direcao = ESQUERDA; break;
                case 'd': case 'D': if (cobra.direcao != ESQUERDA) cobra.direcao = DIREITA; break;
                case 'q': case 'Q':
                    salvarJogo();
                    destruirCobra();
                    goto fim_jogo;
            }
        }
        screenGotoxy(cobra.corpo[cobra.comprimento - 1].x, cobra.corpo[cobra.comprimento - 1].y);
        printf(" ");
        moverCobra();
        if (verificarColisao()) break;
        if (verificarComida()) desenharComida();
        desenharCobra();
        desenharPontuacao();
    }

    destruirCobra();

fim_jogo:
    screenClose();
    keyboardClose();
    timerDestroy();
return ;
}
