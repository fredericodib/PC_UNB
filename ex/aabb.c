/*

ALUNO: FREDERICO PINHEIRO DIB
PROFESSOR: ALCHIERI
ESTUDO DIRIGIDO 13 - PROGRAMAÇÃO CONCORRENTE - 1/2019

*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1
#define THREADS 20

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* lock pro contador*/
pthread_mutex_t print_b = PTHREAD_MUTEX_INITIALIZER; /* lock pro contador*/
pthread_mutex_t print_c = PTHREAD_MUTEX_INITIALIZER; /* lock pro contador*/
pthread_mutex_t print_d = PTHREAD_MUTEX_INITIALIZER; /* lock pro contador*/
int count = 0;

void *ab(void *arg){
  pthread_mutex_lock(&mutex);
  if (count == 0) {
    pthread_mutex_lock(&print_b);
    pthread_mutex_lock(&print_c);
    pthread_mutex_lock(&print_d);
  }
  printf("A");
  count++;
  if (count == THREADS) {
    pthread_mutex_unlock(&print_b);
  }
  pthread_mutex_unlock(&mutex);
  pthread_mutex_lock(&print_b);
  pthread_mutex_unlock(&print_b);
  printf("B");
  
  pthread_exit(0);
}

void *cd(void *arg){
  pthread_mutex_lock(&mutex);
  if (count == 0) {
    pthread_mutex_lock(&print_c);
  }
  printf("C");
  count++;
  if (count == THREADS) {
    pthread_mutex_unlock(&print_b);
  }
  pthread_mutex_unlock(&mutex);
  pthread_mutex_lock(&print_b);
  pthread_mutex_unlock(&print_b);
  printf("D");
  
  pthread_exit(0);
}

int main()
{

  pthread_t  abt[THREADS];
  pthread_t  cdt[THREADS];
  int i;
  int *id;

  for (i = 0; i < THREADS; i++)
  {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&abt[i], NULL, ab, (void *)(id));
  }

  for (i = 0; i < THREADS; i++)
  {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&cdt[i], NULL, cd, (void *)(id));
  }

  for (i = 0; i < THREADS; i++)
  {
    pthread_join(abt[i], NULL);
  }
  for (i = 0; i < THREADS; i++)
  {
    pthread_join(cdt[i], NULL);
  }

  return 0;
}