/*

ALUNO: FREDERICO PINHEIRO DIB - 15/0125925
PROFESSOR: ALCHIERI
ESTUDO DIRIGIDO 7 - Barbeiro - 1/2019

*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define TRUE 1
#define CADEIRAS 5
#define BARBEIROS 1
#define CLIENTES 15

pthread_t cliente[CLIENTES], barbeiro[BARBEIROS];
sem_t cadeira, cadeira_barbeiro, barb, cortando;

void *barbeiros(void *arg){

  int id = *((int *)arg);

  while (TRUE){
    sem_wait(&barb);
    printf("\nBarbeiro %d acorda e vai cortar cabelo\n", id);
    sleep(5);
    printf("Barbeiro %d acabou de cortar o cabelo, foi dormir\n\n", id);
    sem_post(&cortando);
  }

  pthread_exit(0);
}

void *clientes(void *arg){

  int id = *((int *)arg);

  while (TRUE){

    if(sem_trywait(&cadeira) == 0){
      printf("Cliente %d entrou na loja e sentou numa cadeira\n", id);
      sem_wait(&cadeira_barbeiro);
      printf("Cliente %d se levantou para ir até a cadeira do barbeiro, acordando o barbeiro\n", id);
      sem_post(&cadeira);
      sem_post(&barb);
      printf("Cliente %d está cortando o cabelo\n", id);
      sem_wait(&cortando);
      printf("Cliente %d teve o cabelo cortado, vazando da loja\n", id);
      sem_post(&cadeira_barbeiro);
    }
    else{
      printf("Cliente %d não entrou na loja\n", id);
    }
    sleep(15);
  }

  pthread_exit(0);
}

int main(){

  int i;
  int *id;

  sem_init(&cadeira, 0, CADEIRAS);
  sem_init(&cadeira_barbeiro, 0, 1);
  sem_init(&cortando, 0, 0);
  sem_init(&barb, 0, 0);


  for (i = 0; i < CLIENTES; i++)
  {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&cliente[i], NULL, clientes, (void *)(id));
  }

  for (i = 0; i < BARBEIROS; i++)
  {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&barbeiro[i], NULL, barbeiros, (void *)(id));
  }

  pthread_join(cliente[0], NULL);
  pthread_join(barbeiro[0], NULL);

  return 0;
}