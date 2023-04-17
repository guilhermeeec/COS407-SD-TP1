#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "utils.h"

#define PORTA 8080
#define IP "127.0.0.1"
#define TAMANHO_RESPOSTA 16
#define QNT_NUMEROS 3

int main(int argc, char const *argv[])
{
    char numero[NUM_BYTES] = {'\0'};
    char resposta[TAMANHO_RESPOSTA] = {'\0'};
    int ultimo_numero = 0;
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Erro criando socket \n");
        return -1;
    }
    printf("Socket criado\n");

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORTA);

    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) {
        printf("Endereco invalido\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Nao foi possivel conectar \n");
        return -1;
    }
    printf("Conexao efetuada\n");
    
    srand(time(NULL));
    for(int indice_numero = 0; indice_numero < QNT_NUMEROS; indice_numero++) {
        ultimo_numero = gerar_numero(ultimo_numero);
        snprintf(numero, NUM_BYTES, "%d", ultimo_numero);

        send(sock, numero, NUM_BYTES, 0);
        printf("%02d) Numero %d enviado\n", indice_numero+1, ultimo_numero);

        recv(sock, resposta, TAMANHO_RESPOSTA, 0);
        printf("Resposta: %s\n", resposta);
        memset(resposta, 0 ,TAMANHO_RESPOSTA);
        sleep(1);
    }
    snprintf(numero, NUM_BYTES, "0");
    send(sock, numero, NUM_BYTES, 0);
    recv(sock, resposta, TAMANHO_RESPOSTA, 0);
    printf("Resposta: %s\n", resposta);
    close(sock);
    return 0;
}
