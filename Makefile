CC = gcc
CFLAGS = -Wall

signals: signal_tx signal_rx
pipe: pipes-T1 utils.o 
sockets: produtor_socket consumidor_socket utils.o

all: signals pipe sockets

signal_tx: signal_tx.c
	$(CC) $(CFLAGS) -c signal_tx.c -o signal_tx.o
	$(CC) $(CFLAGS) signal_tx.c -o signal_tx.o

signal_rx: signal_rx.c
	$(CC) $(CFLAGS) -c signal_rx.c -o signal_rx.o
	$(CC) $(CFLAGS) signal_rx.c -o signal_rx.o

pipes-T1: pipes-T1.c utils.o
	$(CC) $(CFLAGS) -c pipes-T1.c -o pipes-T1.o
	$(CC) $(CFLAGS) pipes-T1.o utils.o -o pipes-T1

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c -o utils.o

produtor_socket: produtor_socket.c utils.o
	$(CC) $(CFLAGS) -c produtor_socket.c -o produtor_socket.o
	$(CC) $(CFLAGS) produtor_socket.o utils.o -o produtor_socket

consumidor_socket: consumidor_socket.c utils.o
	$(CC) $(CFLAGS) -c consumidor_socket.c -o consumidor_socket.o
	$(CC) $(CFLAGS) consumidor_socket.o utils.o -o consumidor_socket

clean:
	rm -f signal_tx signal_rx pipes-T1 utils produtor_socket consumidor_socket 
	rm -f signal_tx.o signal_rx.o pipes-T1.o utils.o produtor_socket.o consumidor_socket.o utils.o
