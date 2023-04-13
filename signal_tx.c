#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>

#define NUM_ARG 3

int pega_arg_pid(pid_t* p_pid, char* arg_str) 
{
    char* endptr = NULL;
    *p_pid = (pid_t)strtoul(arg_str, &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE) {
        printf("Erro no argumento <pid> no caractere: %c\n", *endptr);
        return -1;
    }    
}

int pega_arg_sig(int* p_sig, char* arg_str) 
{
    char* endptr = NULL;
    *p_sig = (pid_t)strtoul(arg_str, &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE) {
        printf("Erro no argumento <sig> no caractere: %c\n", *endptr);
        return -1;
    }    
}

int main(int argc, char** argv)
{
    if(argc != NUM_ARG) {
        printf("Numero incorreto de argumentos.\nUso: %s <pid> <sig>\n", argv[0]);
        return -1;
    }

    pid_t pid = 0;
    if(pega_arg_pid(&pid, argv[1]))
        return -1;

    int sig = 0;
    if(pega_arg_sig(&sig, argv[2]))
        return -1;

    if(kill(pid, sig) == -1) {
        printf("Erro ao enviar o sinal\n");
        exit(1);
    }

    printf("Sinal enviado com sucesso para o processo %d\n", pid);

    return 0;
}
