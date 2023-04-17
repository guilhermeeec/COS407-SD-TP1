#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

#define QNT_NUMEROS 5

void consumidor(int descritor_leitura) {
    FILE *leitura;
    char numero[NUM_BYTES];
    size_t total_lido;

    leitura = fdopen(descritor_leitura, "r");
    if (!leitura) {
        printf("Erro ao abrir a leitura do Pipe.\n");
        exit(EXIT_FAILURE);
    }
    while((total_lido = fread(numero, NUM_BYTES, 1, leitura) > 0)) { 
        if (total_lido != 1) {
            printf("Erro ao ler do Pipe.\n");
            exit(EXIT_FAILURE);
        }
        if (!(strcmp(numero, "0"))) {
            exit(EXIT_SUCCESS);
        } else if (checar_primo(atoi(numero)) == PRIMO) {
            printf("%s é Primo.\n", numero);
        } else {
            printf("%s não é Primo.\n", numero);
        }
    }
}

void produtor(int descritor_escrita, int qnt_de_num) {
    FILE *leitura;
    char numero[NUM_BYTES];
    size_t total_escrito;
    int ultimo_numero = 0;

    leitura = fdopen(descritor_escrita, "w");
    if (!leitura) {
        printf("Erro ao abrir a escrita do Pipe.\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    sprintf(numero, "%d", gerar_numero(ultimo_numero));
    while (qnt_de_num > 0) {
        total_escrito = fwrite(numero, NUM_BYTES, 1, leitura);
        if (total_escrito != 1) {
            printf("Erro ao escrever no Pipe.\n");
            exit(EXIT_FAILURE);
        }
        ultimo_numero += atoi(numero);
        sprintf(numero, "%d", gerar_numero(ultimo_numero));
        qnt_de_num--;
    }
    strncpy(numero, "0", NUM_BYTES);
    total_escrito = fwrite(numero, NUM_BYTES, 1, leitura);
    if (total_escrito != 1) {
        printf("Erro ao escrever no Pipe.\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}


int main() {
    int pid;
    int pipeT1[2];

    if (pipe(pipeT1)) { // Criar o Pipe
        printf("Erro ao Criar o Pipe.\n");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid < 0) {
        printf("Erro ao Fazer o Fork.\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Processo Consumidor
        close(pipeT1[1]);
        consumidor(pipeT1[0]);
        exit(EXIT_SUCCESS);
    } else {               // Processo Produtor
        close(pipeT1[0]);
        produtor(pipeT1[1], QNT_NUMEROS);
        exit(EXIT_SUCCESS);
    }
}