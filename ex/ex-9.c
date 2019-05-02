/*

ALUNO: FREDERICO PINHEIRO DIB - 15/0125925
PROFESSOR: ALCHIERI
ESTUDO DIRIGIDO 9 - Pombo semaforo - 1/2019

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
sem_t espaco, mutex, cheio;
int contador = 0;

void *usuarios(void *arg){

  int id = *((int *)arg);

  while (TRUE){
    sem_wait(&espaco);
    sem_wait(&mutex);
    contador++;
    printf("Usuario %d coloca uma carta\n%d cartas na mochila\n", id, contador);
    if (contador == CARTAS) {
      printf("Mochila cheia, acorda Pombo\n\n");
      sem_post(&cheio);
    }
    sem_post(&mutex);
    sleep(2);
  }

  pthread_exit(0);
}

void *pombos(void *arg){

  int id = *((int *)arg);
  int i;

  while (TRUE){

    sem_wait(&cheio);
    sem_wait(&mutex);
    printf("Pombo %d acordou\n", id);
    printf("Pombo %d Viajando para B\n", id);
    sleep(3);
    printf("Pombo %d chega em B\n", id);
    printf("Pombo %d comeca a entregar as cartas\n", id);
    contador = 0;
    for (i=0;i<CARTAS;i++) {
      sem_post(&espaco);
    }
    printf("Pombo %d termina de entregar as cartas\n", id);
    printf("Pombo %d Volta para A\n", id);
    sleep(3);
    printf("Pombo %d chega em A\n", id);
    printf("Pombo %d Pombo dorme\n\n", id);
    sem_post(&mutex);
  }

  pthread_exit(0);
}

int main(){

  int i;
  int *id;

  sem_init(&espaco, 0, CARTAS);
  sem_init(&mutex, 0, 1);
  sem_init(&cheio, 0, 0);

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