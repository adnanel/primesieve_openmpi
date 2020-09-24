#include <iostream>
#include "Sieve.h"

#include <mpi.h>
#include <cstdio>

int numResults(int min, int max) {
    Sieve sieve;
    auto res = sieve.sieveOfEratosthenes(min, max);
    return res.size();
}

/*
int main(int argc, char** argv) {

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

    int range[2];
    int size = 2E9 / 4;
    int sum = 0;
    for (int i = 0; i <= 2E9 - size; i += size) {
        range[0] = i;
        range[1] = i + size;

        if (rank == 0) {
            MPI_Send(range, 2, MPI_INT, 1, 0, MPI_COMM_WORLD);
        } else {
            MPI_Recv(range, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << rank << ": I'm looking for primes in the range " << range[0] << " and " << range[1] << std::endl;
        }
    }

    MPI_Finalize();
}