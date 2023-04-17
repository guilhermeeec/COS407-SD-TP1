#!/bin/bash
touch logs.txt

echo "1. Sinais"
make signals

# ---------------------------------------

echo "1.1. Busy waiting" 
./signal_rx busy >> logs.txt 2>&1 &
pid=$!

sleep 4
echo "1.1.1. Enviando sinal SIGINT"
./signal_tx $pid 2

sleep 4
echo "1.1.2. Enviando sinal SIGUSR1"
./signal_tx $pid 10

sleep 4
echo "1.1.3. Enviando sinal SIGTERM"
./signal_tx $pid 15

# ---------------------------------------

echo "1.2. Blocking waiting" 
./signal_rx blocking >> logs.txt 2>&1 &
pid=$!

sleep 4
echo "1.2.1. Enviando sinal SIGINT"
./signal_tx $pid 2

sleep 4
echo "1.2.2. Enviando sinal SIGUSR1"
./signal_tx $pid 10

sleep 4
echo "1.2.3. Enviando sinal SIGTERM"
./signal_tx $pid 15

make clean