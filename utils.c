#include <time.h>
#include <stdlib.h>

#define NUM_BYTES   20
#define PRIME       1
#define NOT_PRIME   2

int checkPrime(int number) {
    if (number == 1) {
        return NOT_PRIME;
    }
    for (int idx = 2; idx <= number/2; idx++) {
        if (!(number % idx)) {
            return NOT_PRIME;
        }
    }
    return PRIME;
}

int genNumber(int lastNumber) {
    srand(time(NULL));
    int r = rand() % 100;
    return lastNumber + r;
}