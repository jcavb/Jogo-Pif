#include "timer.h"

void timerInit(int valueMilliSec) {
    // Inicialização simples, sem nada específico
}

void timerDestroy() {
    // Finalização simples, sem nada específico
}

void timerSleep(int milliseconds) {
    // Loop de espera para simular uma pausa
    volatile long long int i, j;
    for (i = 0; i < milliseconds * 1000; i++) {
        for (j = 0; j < 100; j++) {
            // Laço vazio
        }
    }
}
