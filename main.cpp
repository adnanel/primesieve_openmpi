#include <iostream>
#include "Sieve.h"

#include <mpi.h>
#include <cstdio>


void distributeTasks(int rank, int min, int max, int size, int numtasks) {
    int range[2];
    int nextWorker = rank + 1;

    for (int i = min; i <= max - size; i += size) {
        range[0] = i;
        range[1] = i + size;

        std::cout << rank << ": Sending task to worker " << nextWorker << std::endl;
        MPI_Send(range, 2, MPI_INT, nextWorker, 0, MPI_COMM_WORLD);

        nextWorker = (nextWorker + 1) % numtasks;
        if (nextWorker == rank) {
            nextWorker = (nextWorker + 1) % numtasks;
        }
    }

    range[0] = range[1] = -1;
    for (int i = 1; i < numtasks; ++ i) {
        MPI_Send(range, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
}

void doTasks(int rank) {
    Sieve sieve;
    int range[2];

    while (true) {
        MPI_Recv(range, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (range[0] < 0 && range[1] < 0) {
            break;
        }
        std::cout << rank << ": I'm looking for primes in the range " << range[0] << " and " << range[1] << std::endl;

        auto res = sieve.sieveOfEratosthenes(range[0], range[1]);

        std::cout << rank << ": Found " << res.size() << " primes." << std::endl;
    }
    std::cout << rank << ": Shutting down" << std::endl;
}

int main(int argc, char *argv[]) {
    int numtasks, rank, rc;
    rc = MPI_Init(&argc, &argv);
    if (rc != MPI_SUCCESS) {
        printf("Error starting MPI program. Terminating.\n");
        MPI_Abort(MPI_COMM_WORLD, rc);
    }

    char portName[1024];
    int usedPort = MPI_Open_port(MPI_INFO_NULL, portName);
    std::cout << "Using port " << usedPort << ": " << portName << std::endl;

    int number;
    std::cout << "N=";
    std::cin >> number;

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        int size = number / (numtasks - 1);
        distributeTasks(rank, 0, 2E9, size, numtasks);
    } else {
        doTasks(rank);
    }
    MPI_Finalize();
}