//
// Created by adnan on 23/09/2020.
//

#ifndef PRIMESIEVE_SIEVE_H
#define PRIMESIEVE_SIEVE_H

#include <vector>
#include <cmath>

class Sieve {
    int max(int a, int b) {
        return a < b ? b : a;
    }

public:
    std::vector<int> sieveOfEratosthenes(int lowBound, int upperBound) {
        int lowerBound = max(2, lowBound);
        int sqrt = (int) std::sqrt(upperBound);

        int range = upperBound - lowerBound;

        bool* primeChecks = new bool[range + 1];

        for (int i = 0; i < range + 1; ++ i) {
            primeChecks[i] = true;
        }

        std::vector<int> helperNumbers;
        if (range < 1000) {
            for (int p = 2; p <= sqrt; ++p) {
                if (p % 2 != 0) {
                    helperNumbers.push_back(p);
                }
            }
        } else {
            helperNumbers = sieveOfEratosthenes(0, sqrt);
        }

        for (int p : helperNumbers) {
            int kp = max(p * p, lowerBound);
            while (kp % p != 0) {
                kp++;
            }

            for (int i = kp; i <= upperBound; i += p) {
                primeChecks[i - lowerBound] = false;
            }
        }

        std::vector<int> result;

        for (int i = 0; i < range + 1; ++i) {
            if (primeChecks[i]) {
                result.push_back(i + lowerBound);
            }
        }

        delete[] primeChecks;
        return result;
    }
};


#endif //PRIMESIEVE_SIEVE_H
