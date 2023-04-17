#include <time.h>
#include <stdlib.h>
#include "utils.h"

int checar_primo(int number) {
    if (number == 1) {
        return NOT_PRIMO;
    }
    for (int idx = 2; idx <= number/2; idx++) {
        if (!(number % idx)) {
            return NOT_PRIMO;
        }
    }
    return PRIMO;
}

int gerar_numero(int lastNumber) {
    int r = rand() % 100;
    return lastNumber + r;
}