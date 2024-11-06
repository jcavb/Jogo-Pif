#ifndef TIMER_H
#define TIMER_H

// Inicializa o temporizador (não faz nada especial aqui, mas está para manter a consistência)
void timerInit(int valueMilliSec);

// Pausa a execução por um número especificado de milissegundos
void timerSleep(int milliseconds);

// Finaliza o temporizador (não faz nada especial aqui, mas está para manter a consistência)
void timerDestroy();

#endif /* TIMER_H */
