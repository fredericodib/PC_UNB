#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"

#define AV 5



pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cheio = PTHREAD_COND_INITIALIZER;
pthread_cond_t vazio = PTHREAD_COND_INITIALIZER;

int N = 50;
int count = 0;

void * consumidor (void * arg) {
    int id = *((int *) arg);
    while (1) {
        pthread_mutex_lock(&lock);

        pthread_cond_wait(&vazio, &lock);
        printf("Pombo: Estou levando %d mensagens\n",count);
        sleep(1);
        count = 0;
        printf("Pombo: Voltei\n");
        pthread_cond_broadcast(&cheio);
        pthread_mutex_unlock(&lock);
    }
}

void * produtor (void * arg) {
    int id = *((int *) arg);
    while (1) {
        pthread_mutex_lock(&lock);
        while (count == N) {
            pthread_cond_wait(&cheio,&lock);
        }
        printf("Carteiro%d Estou colocando uma carta.\n",id);
        sleep(1);
        count++;
        printf("Carteiro%d coloquei uma carta.Numero de cartas = %d.\n",id, count);
        if (count == N) {
            pthread_cond_signal(&vazio);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

}

int main() {
    pthread_t carteiro[AV];
    pthread_t pombo;
    int i;
    int *id;

    id = (int *) malloc(sizeof(int));
    *id = i;
    pthread_create(&pombo, NULL, consumidor, (void *) (id));
    for (i = 0; i < AV ; i++) {
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&carteiro[i], NULL, produtor, (void *) (id));
    }

    pthread_join(pombo,NULL);
    for (i = 0; i < AV ; i++) {
      pthread_join(carteiro[i],NULL);
    }

    return 0;
}
