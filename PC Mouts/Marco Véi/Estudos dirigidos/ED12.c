#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include <mpi.h>


#define NUM 50;

int main(int argc, char *argv[]) {
    int myid, otherid, size;
    int i, tag = 1;
    int item = 0, empty;
    int buffer = 0;
    int consumido = 0;
    int max = NUM;
    MPI_Status status;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (myid == 0) {
       otherid = 1;
    }
    else {
       otherid = 0;
    }

    if (myid == 0) {
        while(1) {
            printf("Produzindo...\n");
            buffer++;
            sleep(2);
            MPI_Recv(&empty, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            item = 1;
            MPI_Send(&item, 1, MPI_INT, otherid, tag, MPI_COMM_WORLD);
            buffer--;
        }
    }
    else{
        empty = 0;
        for (i = 0;i < max;i++) {
            MPI_Send(&empty, 1, MPI_INT, otherid, tag, MPI_COMM_WORLD);
        }
        while (1) {
            MPI_Recv(&item, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            consumido++;
            printf("Consumindo... total consumido = %d\n", consumido);
            sleep(2);
            MPI_Send(&empty, 1, MPI_INT, otherid, tag, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();

}
