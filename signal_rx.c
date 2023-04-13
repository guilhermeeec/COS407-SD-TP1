#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ARG 2

typedef enum {BUSY, BLOCKING} modo_espera_t;

void sigint_handler(int signum) {
    printf("Recebeu SIGINT (%d).\n", signum);
}

void sigterm_handler(int signum) {
    printf("Recebeu SIGTERM (%d).\n", signum);
    exit(0);
}

void sigusr1_handler(int signum) {
    printf("Recebeu SIGUSR1 (%d).\n", signum);
}

int pega_arg_espera(modo_espera_t* p_tipo_espera, char* arg_str) 
{
    printf("Meu PID: %d\n", getpid());

    if(!strcmp(arg_str, "busy")) {
        printf("Modo de espera: busy\n");
        *p_tipo_espera = BUSY;
        return 0;
    }
    else if(!strcmp(arg_str, "blocking")) {
        printf("Modo de espera: blocking\n");
        *p_tipo_espera = BLOCKING;
        return 0;
    }
    else {
        printf("Modo de espera invalido\n");
        return -1;
    }
}

void espera_sinais_busy() {
    while (1) {
        sleep(2);
        printf("Ainda nao recebi um sinal, mas estou usando a CPU...\n");
    }
}

void espera_sinais_blocking() {
    while (1) {
        printf("Vou dormir pra nao ficar usando CPU.\n");
        pause();
    }
}

int main(int argc, char** argv) 
{
    if(argc != NUM_ARG) {
        printf("Numero incorreto de argumentos.\nUso: %s [busy/blocking]\n", argv[0]);
        return -1;
    }

    modo_espera_t tipo_espera = BUSY;
    if(pega_arg_espera(&tipo_espera, argv[1]))
        return -1;

    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);
    signal(SIGUSR1, sigusr1_handler);

    printf("Esperando sinais...\n");
    printf("(SIGINT ou SIGTERM ou SIGUSR1)\n");
    switch(tipo_espera) {
        case BUSY:
        espera_sinais_busy();
        break;

        case BLOCKING:
        espera_sinais_blocking();
        break;

        default:
        printf("Erro inesperado!\n");
        break;
    }
    
    return 0;
}