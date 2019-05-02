/*

ALUNO: FREDERICO PINHEIRO DIB - 15/0125925
PROFESSOR: ALCHIERI
ESTUDO DIRIGIDO 8 - Pombo conds - 1/2019

*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define TRUE 1
#define CARTAS 20
#define POMBO 1
#define USUARIOS 5

pthread_t pombo[POMBO], usuario[USUARIOS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* lock pro contador*/
pthread_cond_t p = PTHREAD_COND_INITIALIZER; 
pthread_cond_t u = PTHREAD_COND_INITIALIZER; 
int contador = 0;

void *usuarios(void *arg){

  int id = *((int *)arg);

  while (TRUE){
    pthread_mutex_lock(&mutex);
    while (contador == CARTAS) {
      pthread_cond_wait(&u, &mutex);
    }
    contador++;
    printf("Usuario %d coloca uma carta\n%d cartas na mochila\n", id, contador);
    if (contador == CARTAS) {
        printf("Mochila cheia, acorda Pombo\n\n");
        pthread_cond_signal(&p);
    }
    pthread_mutex_unlock(&mutex);
    sleep(2);
  }

  pthread_exit(0);
}

void *pombos(void *arg){

  int id = *((int *)arg);

  while (TRUE){

    pthread_mutex_lock(&mutex);
    while(contador != 20){
      pthread_cond_wait(&p, &mutex);
    }
    printf("Pombo %d acordou\n", id);
    printf("Pombo %d Viajando para B\n", id);
    sleep(3);
    printf("Pombo %d chega em B\n", id);
    printf("Pombo %d comeca a entregar as cartas\n", id);
    contador = 0;
    printf("Pombo %d termina de entregar as cartas\n", id);
    printf("Pombo %d Volta para A\n", id);
    sleep(3);
    printf("Pombo %d chega em A\n", id);
    printf("Pombo %d Pombo dorme\n\n", id);
    pthread_cond_signal(&u);
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(0);
}

int main(){

  int i;
  int *id;

  for (i = 0; i < USUARIOS; i++)
  {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&usuario[i], NULL, usuarios, (void *)(id));
  }

  for (i = 0; i < POMBO; i++)
  {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&pombo[i], NULL, pombos, (void *)(id));
  }

  pthread_join(pombo[0], NULL);
  pthread_join(usuario[0], NULL);

  return 0;
}