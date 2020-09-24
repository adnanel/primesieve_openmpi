#include <iostream>
#include "Sieve.h"

#include "mpi.h"
#include <stdio.h>

int numResults(int min, int max) {
    Sieve sieve;
    auto res = sieve.sieveOfEratosthenes(min, max);
    return res.size();
}

/*
int main(int argc, char** argv) {
    int size = 2E9 / 4;
    int sum = 0;
    for (int i = 0; i <= 2E9 - size; i += size) {
        sum += numResults(i, i + size);
    }

    std::cout << sum;

    return 0;
}
*/

int main(int argc, char *argv[]) {
    int numtasks, rank, rc;
    rc = MPI_Init(&argc, &argv);
    if (rc != MPI_SUCCESS) {
        printf("Error starting MPI program. Terminating.\n");
        MPI_Abort(MPI_COMM_WORLD, rc);
    }

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Hello, World from rank %d out of %d\n", rank, numtasks);
    MPI_Finalize();
}