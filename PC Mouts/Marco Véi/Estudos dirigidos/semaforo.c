#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"

#define AV 5

pthread_t consumi[AV];
int n = 5
sem_t pista;
sem_t esquipe[n];

void * pilotos(void * arg) {
  int id = *((int *) arg);
  while (1) {

  }

}


int main() {
  int i;
  int *id;
  for (i = 0; i < AV ; i++) {
      id = (int *) malloc(sizeof(int));
      *id = i;
      pthread_create(&produt[i], NULL, produtor, (void *) (id));
  }
  return 0;
}
