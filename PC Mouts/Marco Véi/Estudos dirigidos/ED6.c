#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"

#define AV 5

sem_t lock;
sem_t lug_cheio;
sem_t lug_vaz;
int N = 50;
int count = 0;

void * produtor (void * arg) {
    int id = *((int *) arg);
    while (1) {

        sem_wait(&lug_vaz);
        sem_wait(&lock);
        sem_post(&lug_cheio);
        sleep(1);
        count++;
        printf("Produtor%d Produz count = %d.\n", id, count);
        sem_post(&lock);
        sleep(1);
    }
    pthread_exit(0);
}

void * consumidor (void * arg) {
    int id = *((int *) arg);
    while (1) {

        sem_wait(&lug_cheio);
        sem_wait(&lock);
        sleep(1);
        count--;
        printf("Consumidor%d Consume count = %d.\n",id, count);
        sem_post(&lug_vaz);
        sem_post(&lock);
    }

    pthread_exit(0);
}


int main() {
    pthread_t produt[AV];
    pthread_t consumi[AV];
    sem_init(&lug_cheio, 0, 0);
    sem_init(&lug_vaz, 0, N);
    sem_init(&lock, 0, 1);
    int i;
    int *id;
    for (i = 0; i < AV ; i++) {
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&produt[i], NULL, produtor, (void *) (id));
    }
    for (i = 0; i < AV ; i++) {
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&consumi[i], NULL, consumidor, (void *) (id));
    }

    pthread_join(produt[0],NULL);
    pthread_join(consumi[0],NULL);

    return 0;
}
