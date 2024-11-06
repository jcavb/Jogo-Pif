#include "timer.h"

void timerInit(int valueMilliSec) {
    // Configuração inicial, se necessário
}

void timerDestroy() {
    // Finalização, se necessário
}

void timerSleep(int milliseconds) {
    usleep(milliseconds * 1000); // Converte milissegundos para microssegundos
}
