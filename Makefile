CC = gcc
CFLAGS = -Wall

SIGNALS_SRCS = signal_tx.c signal_rx.c
PIPES_SRCS = pipes.c utils.c
SOCKETS_SRCS = produtor_socket.c consumidor_socket.c utils.c

all: signals pipes sockets

signals: $(SIGNALS_SRCS:.c=.o)
	$(CC) -o signal_tx signal_tx.o
	$(CC) -o signal_rx signal_rx.o

pipes: $(PIPES_SRCS:.c=.o)
	$(CC) -o pipes $(PIPES_SRCS:.c=.o)

sockets: $(SOCKETS_SRCS:.c=.o)
	$(CC) -o produtor_socket produtor_socket.o utils.o
	$(CC) -o consumidor_socket consumidor_socket.o utils.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f signal_tx signal_rx pipes produtor_socket consumidor_socket $(wildcard *.o)
