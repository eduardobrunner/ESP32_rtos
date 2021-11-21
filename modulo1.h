#ifndef _MODULO1_H_
#define _MODULO1_H_

#define APP_CORE 1

#include <Arduino.h>

typedef struct data_t
{
    int valor;
    char msg[15];
};


void modulo1_launch();
void modulo1_kill();
void modulo1_send(data_t *msg);

#endif