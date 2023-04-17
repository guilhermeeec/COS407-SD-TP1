CC = gcc
CFLAGS = -Wall

signals: signal_tx signal_rx

all: signal_tx signal_rx

signal_tx: signal_tx.c
	$(CC) $(CFLAGS) -o signal_tx signal_tx.c

signal_rx: signal_rx.c
	$(CC) $(CFLAGS) -o signal_rx signal_rx.c

clean:
	rm -f signal_tx signal_rx
