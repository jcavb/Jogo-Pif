#include "timer.h"

void timerInit(int valueMilliSec) {}

void timerDestroy() {}

void timerSleep(int milliseconds) {
    volatile long long int i, j;
    for (i = 0; i < milliseconds * 1000; i++) {
        for (j = 0; j < 100; j++) {
            // Laço vazio para simular espera
        }
    }
}
