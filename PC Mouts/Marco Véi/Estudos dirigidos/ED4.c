#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"

#define AV 5


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cheio = PTHREAD_COND_INITIALIZER;
pthread_cond_t vazio = PTHREAD_COND_INITIALIZER;
int buffer[100];



int N = 100;
int count;

void * produtor (void * arg) {
    int id = *((int *) arg);
    while (1) {
        pthread_mutex_lock(&lock);
        while (count == N - 1) {
            pthread_cond_wait(&cheio, &lock);
        }
        buffer[count] = 1;
        count++;
        printf("Produzi count = %d.\n",count);
        if(count == 1) {
            pthread_cond_signal(&vazio);
        }
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
        printf("Consumi count = %d.\n",count);
        if(count == N - 2) {
            pthread_cond_signal(&cheio);
        }
        pthread_mutex_unlock(&lock);
    }

}

int main() {
    pthread_t produt[AV];
    pthread_t consumi[AV];
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
