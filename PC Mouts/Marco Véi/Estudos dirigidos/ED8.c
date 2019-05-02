#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"

#define AV 20

sem_t cliente;
sem_t disponivel;
sem_t cadeiras;
sem_t cortando;
int N = 4;

void * Barbeiro (void * arg) {
    int id = *((int *) arg);
    while (1) {

        sem_wait(&cliente);
        sleep(2);
        printf("Barbeiro cortou o cabelo de um cliente.\n");
        sem_post(&cortando);
    }
    pthread_exit(0);
}

void * Cliente (void * arg) {
    int id = *((int *) arg);


    if (sem_trywait(&cadeiras) == 0) {
        printf("Cliente%d esperando para ser atendido.\n",id);
        sem_wait(&disponivel);
        sem_post(&cadeiras);
        sem_post(&cliente);
        printf("Cliente%d sentou na cadeira.\n",id);
        printf("Cliente%d cortando o cabelo.\n",id);
        sem_wait(&cortando);
        printf("Cliente%d terminou de cortar\n",id);
        sem_post(&disponivel);
        sleep(3);

    }
    else {
        printf("Cliente%d não entrou.\n", id);
    }


    pthread_exit(0);
}


int main() {
    pthread_t barbeiro;
    pthread_t clientes[AV];
    sem_init(&cliente, 0, 0);
    sem_init(&cadeiras, 0, N);
    sem_init(&disponivel, 0, 1);
    sem_init(&cortando, 0, 0);
    int i;
    int *id;

    id = (int *) malloc(sizeof(int));
    *id = i;
    pthread_create(&barbeiro, NULL, Barbeiro, (void *) (id));

    for (i = 0; i < AV ; i++) {
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&clientes[i], NULL, Cliente, (void *) (id));
    }

    pthread_join(barbeiro,NULL);
    pthread_join(clientes[0],NULL);

    return 0;
}
