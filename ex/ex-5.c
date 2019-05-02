/*

ALUNO: FREDERICO PINHEIRO DIB
PROFESSOR: ALCHIERI
ESTUDO DIRIGIDO 5 - PROGRAMAÇÃO CONCORRENTE - 1/2019

*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1
#define COZINHEIRO 1
#define CANIBAIS 20
#define PANELA 250

pthread_mutex_t l = PTHREAD_MUTEX_INITIALIZER; /* lock pro contador*/
pthread_cond_t co = PTHREAD_COND_INITIALIZER; 
pthread_cond_t ca = PTHREAD_COND_INITIALIZER;
int comida = 0;

void *cozinhando(void *arg){
  int id = *((int *)arg);
  
  while(TRUE){
    pthread_mutex_lock(&l);
    while(comida != 0){
      printf("\nCozinheiro %d no aguardo, existem ainda %d porções de comida\n",id, comida);
      pthread_cond_wait(&co, &l);
    }

    printf("\nCanibais estão sem comida...\nCozinheiro %d indo preparar porções...\n", id);
    sleep(5);
    comida += PANELA;
    printf("Cozinheiro %d preparou %d porções de comida pros canibais laricados\n",id, comida);
    printf("\n");
    pthread_cond_broadcast(&ca);
    pthread_mutex_unlock(&l);
  }
  pthread_exit(0);
}

void *comendo(void *arg){
  int id = *((int*)arg);

  while (TRUE){
    pthread_mutex_lock(&l);
    while(comida == 0){
      printf("\nCanibal %d: estou aguardando o cozinheiro preparar porções\n", id);
      pthread_cond_wait(&ca, &l);
    }
    printf("Canibal %d: Vou comer... ainda existem %d porções\n", id, comida);
    comida--;
    if(comida == 0){
      printf("Canibal %d: Acabou a comida, vou acordar o cozinheiro\n", id);
      pthread_cond_signal(&co);
    }
    printf("\n");
    pthread_mutex_unlock(&l);
    sleep(rand() % 5);
  }
  pthread_exit(0);
}

int main()
{

  pthread_t cozinheiro[COZINHEIRO], canibais[CANIBAIS];
  int i;
  int *id;

  for (i = 0; i < COZINHEIRO; i++)
  {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&cozinheiro[i], NULL, cozinhando, (void *)(id));
  }

  for (i = 0; i < CANIBAIS; i++)
  {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&canibais[i], NULL, comendo, (void *)(id));
  }

  pthread_join(cozinheiro[0], NULL);
  pthread_join(canibais[0], NULL);

  return 0;
}