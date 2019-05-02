#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"

#define AV 5



pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cheio = PTHREAD_COND_INITIALIZER;
pthread_cond_t vazio = PTHREAD_COND_INITIALIZER;


int count = 0;

void * produtor (void * arg) {
    int id = *((int *) arg);
    while (1) {
        pthread_mutex_lock(&lock);
        while (count != 0) {
            pthread_cond_wait(&cheio, &lock);
        }
        count = 10;
        printf("Produzi count = %d.\n",count);
        pthread_cond_broadcast(&vazio);
        pthread_mutex_unlock(&lock);
    }
}

void * consumidor (void * arg) {
    int id = *((int *) arg);
    while (1) {
        pthread_mutex_lock(&lock);
        while (count == 0) {
            pthread_cond_wait(&vazio,&lock);
        }
        count--;
        printf("Canibal%d Consumiu count = %d.\n",id, count);
        if (count == 0) {
            pthread_cond_signal(&cheio);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

}

int main() {
    pthread_t Canibal[AV];
    pthread_t cozinheiro;
    int i;
    int *id;

    id = (int *) malloc(sizeof(int));
    *id = i;
    pthread_create(&cozinheiro, NULL, produtor, (void *) (id));
    for (i = 0; i < AV ; i++) {
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&Canibal[i], NULL, consumidor, (void *) (id));
    }

    pthread_join(cozinheiro,NULL);
    for (i = 0; i < AV ; i++) {
      pthread_join(Canibal[i],NULL);
    }

    return 0;
}
