#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "utils.c"

#define PORT 8080
#define TAMANHO_RESPOSTA 16
#define TAMANHO_FILA 5

int main(int argc, char const *argv[]) 
{
    int server_fd, socket_cliente;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char recebido[NUM_BYTES] = {0};
    char resposta[TAMANHO_RESPOSTA] = {'\0'};
    int numero_recebido = 1;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("Erro criando socket \n");
        return -1;
    }
    printf("Socket criado\n");

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                   &opt, sizeof(opt))) {
        printf("Erro configurando socket\n");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        printf("Erro vinculando socket ao endereco do servidor\n");
        return -1;
    }

    if (listen(server_fd, TAMANHO_FILA) < 0) {
        printf("Erro escutando o socket\n");
        return -1;
    }

    if ((socket_cliente = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen)) < 0) {
        printf("Erro escutando o socket\n");
        return -1;
    }

    while(1) {

        memset(recebido, '\0', NUM_BYTES);
        recv(socket_cliente, recebido, NUM_BYTES, 0);
        printf("Recebido: %s\n", recebido);

        memset(resposta, '\0', TAMANHO_RESPOSTA);
        numero_recebido =  atoi(recebido);
        if(numero_recebido == 0) {
            snprintf(resposta, TAMANHO_RESPOSTA, "Fim");
            send(socket_cliente, resposta, strlen(resposta), 0);
            close(socket_cliente);
            return 0;
        }

        if(checkPrime(numero_recebido) == PRIME) 
            snprintf(resposta, TAMANHO_RESPOSTA, "Eh primo");
        else
            snprintf(resposta, TAMANHO_RESPOSTA, "Nao eh primo");

        send(socket_cliente, resposta, strlen(resposta), 0);
        printf("Resposta enviada\n");
    }
}
