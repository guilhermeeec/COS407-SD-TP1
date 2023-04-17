#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "utils.c"

#define PORTA 8080
#define IP "127.0.0.1"
#define TAMANHO_RESPOSTA 16
#define QNT_NUMEROS 5

int envia_numero(char* numero, char* resposta) 
{
    int sock = 0, status_leitura;
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

    send(sock, numero, NUM_BYTES, 0);
    printf("Numero enviado\n");

    status_leitura = recv(sock, resposta, TAMANHO_RESPOSTA, 0);
    return 0;
}

int main(int argc, char const *argv[])
{
    char numero[NUM_BYTES] = {'\0'};
    char resposta[TAMANHO_RESPOSTA] = {'\0'};
    int indice_numero = QNT_NUMEROS;
    int ultimo_numero = 0;

    memset(resposta, '\0', TAMANHO_RESPOSTA); 
    
    for(int indice_numero = 0; indice_numero < QNT_NUMEROS; indice_numero++) {
        ultimo_numero = genNumber(ultimo_numero);
        snprintf(numero, NUM_BYTES, "%d", ultimo_numero);
        if(envia_numero(numero, resposta))
            return -1;
        printf("Resposta: %s\n", resposta);
    }
    if(envia_numero("0", resposta))
        return -1;
    return 0;
}
