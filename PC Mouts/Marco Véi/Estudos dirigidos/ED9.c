#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"
#define N 5
#define PENSAR 0
#define FOME 1
#define COMER 2
#define ESQUERDA (nfilosofo+4)%N
#define DIREITA (nfilosofo+1)%N

void *filosofo(void *arg);
void agarraGarfo(int);
void deixaGarfo(int);
void testar(int);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t S[N];
int estado[N];
int nfilosofo[N]={0,1,2,3,4};

void *filosofo(void * arg) {
    int id = *((int *) arg);
   while(1) {
      printf("Filosofo %d esta a pensar.\n", id+1);
      sleep(1);
      agarraGarfo(id);
      sleep(1);
      deixaGarfo(id);
   }
}

void agarraGarfo(int nfilosofo) {
    pthread_mutex_lock(&lock);
    estado[nfilosofo] = FOME;
    printf("Filosofo %d tem fome.\n", nfilosofo+1);
    testar(nfilosofo);
    pthread_mutex_unlock(&lock);
    sem_wait(&S[nfilosofo]);
    sleep(1);
}

void deixaGarfo(int nfilosofo){
    pthread_mutex_lock(&lock);
    estado[nfilosofo]=PENSAR;
    printf("Filosofo %d deixou os garfos %d e %d.\n", nfilosofo+1, ESQUERDA+1, nfilosofo+1);
    testar(ESQUERDA);
    testar(DIREITA);
    pthread_mutex_unlock(&lock);
}

void testar(int nfilosofo) {
   if(estado[nfilosofo]==FOME && estado[ESQUERDA]
 !=COMER && estado[DIREITA]!=COMER) {
      estado[nfilosofo]=COMER;
      sleep(2);
      printf("Filosofo %d agarrou os garfos %d e %d.\n", nfilosofo+1, ESQUERDA+1, nfilosofo+1);
      printf("Filosofo %d esta a comer.\n", nfilosofo+1);
      sem_post(&S[nfilosofo]);
   }
}

int main() {
   int i;
   int *id;
   pthread_t thread_id[N];
   for(i=0;i<N;i++) {
      sem_init(&S[i],0,0);
    }
   for(i=0;i<N;i++) {
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&thread_id[i], NULL, filosofo, (void *) id );
   }
   for(i=0;i<N;i++) {
       pthread_join(thread_id[i],NULL);
    }
   return(0);
}
