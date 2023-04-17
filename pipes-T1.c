#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

void consumidor(int readEnd) {
    FILE *read;
    char number[NUM_BYTES];
    size_t totalRead;

    read = fdopen(readEnd, "r");
    if (!read) {
        printf("Erro ao abrir a leitura do Pipe.\n");
        exit(EXIT_FAILURE);
    }
    while((totalRead = fread(number, NUM_BYTES, 1, read) > 0)) { 
        if (totalRead != 1) {
            printf("Erro ao ler do Pipe.\n");
            exit(EXIT_FAILURE);
        }
        if (!(strcmp(number, "0"))) {
            exit(EXIT_SUCCESS);
        } else if (checkPrime(atoi(number)) == PRIME) {
            printf("%s é Primo.\n", number);
        } else {
            printf("%s não é Primo.\n", number);
        }
    }
}

void produtor(int writeEnd, int qntOfNum) {
    FILE *write;
    char number[NUM_BYTES];
    size_t totalWritten;
    int lastNumber = 0;

    write = fdopen(writeEnd, "w");
    if (!write) {
        printf("Erro ao abrir a escrita do Pipe.\n");
        exit(EXIT_FAILURE);
    }
    sprintf(number, "%d", genNumber(lastNumber));
    while (qntOfNum > 0) {
        totalWritten = fwrite(number, NUM_BYTES, 1, write);
        if (totalWritten != 1) {
            printf("Erro ao escrever no Pipe.\n");
            exit(EXIT_FAILURE);
        }
        lastNumber += atoi(number);
        sprintf(number, "%d", genNumber(lastNumber));
        qntOfNum--;
    }
    strncpy(number, "0", NUM_BYTES);
    totalWritten = fwrite(number, NUM_BYTES, 1, write);
    if (totalWritten != 1) {
        printf("Erro ao escrever no Pipe.\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}


int main() {
    int pid;
    int pipeT1[2];
    int qntOfNum = 5;

    if (pipe(pipeT1)) {
        printf("Erro ao Criar o Pipe.\n");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid < 0) {
        printf("Erro ao Fazer o Fork.\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        close(pipeT1[1]);
        consumidor(pipeT1[0]);
        exit(EXIT_SUCCESS);
    } else {
        close(pipeT1[0]);
        produtor(pipeT1[1], qntOfNum);
        exit(EXIT_SUCCESS);
    }
}