#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXSIZE 10000  /* maximum matrix size */
#define MAXWORKERS 100   /* maximum number of workers */

pthread_barrier_t barrier;  
int numWorkers;

int size, stripSize;  /* assume size is multiple of numWorkers */
int sums[MAXWORKERS];
int matrix[MAXSIZE][MAXSIZE];
void *Worker(void *);


int main(int argc, char *argv[]) {
  int i, j;
 
  if(argc != 3) {
    printf("erro na chamada do programa: matriz <#tamanho> <#número threads>\n");
    exit(1);
  }

  pthread_t workerid[MAXWORKERS];
  size = atoi(argv[1]);
  numWorkers = atoi(argv[2]);
  stripSize = size/numWorkers;

  pthread_barrier_init(&barrier, NULL, numWorkers);

  /* initialize the matrix */
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++)
      matrix[i][j] = 1;


  int * id;
  /* create the workers, then exit */
  for (i = 0; i < numWorkers; i++){
     id = (int *) malloc(sizeof(int));
     *id = i;
     pthread_create(&workerid[i], NULL, Worker, (void *) (id));

  }

  for (i = 0; i < numWorkers; i++){
       if(pthread_join(workerid[i], NULL)){
          printf("\n ERROR joining thread");
          exit(1);
       }
  }
  printf("Bye!\n");
}

/* Each worker sums the values in one strip of the matrix.
   After a barrier, worker(0) computes and prints the total */
void * Worker(void *arg) {
  int myid = *(int *)(arg);
  int total, i, j, first, last;

  int self = pthread_self();
 
  printf("worker %d (pthread id %d) has started\n", myid, self);

  /* determine first and last rows of my strip */
  first = myid*stripSize;
  last = first + stripSize - 1;

  /* sum values in my strip */
  total = 0;
  for (i = first; i <= last; i++)
    for (j = 0; j < size; j++)
      total += matrix[i][j];
  sums[myid] = total;
  pthread_barrier_wait(&barrier);
  if (myid == 0) {
    total = 0;
    for (i = 0; i < numWorkers; i++)
      total += sums[i];
    printf("the total is %d\n", total);
  }
 // pthread_exit(0);
}
