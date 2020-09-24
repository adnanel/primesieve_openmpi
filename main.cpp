#include <iostream>
#include "Sieve.h"

int numResults(int min, int max) {
    Sieve sieve;
    auto res = sieve.sieveOfEratosthenes(min, max);
    return res.size();
}

int main() {
    int size = 2E9 / 4;
    int sum = 0;
    for (int i = 0; i <= 2E9 - size; i += size) {
        sum += numResults(i, i + size);
    }

    std::cout << sum;

    return 0;
}
