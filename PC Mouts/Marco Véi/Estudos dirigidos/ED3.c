#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"

#define AV 5

pthread_mutex_t lock_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_b = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t turno = PTHREAD_MUTEX_INITIALIZER;
int nla=0;
int nlb=0;

void * ladoA(void * arg){
    int id = *((int *) arg);
    while (1) {
        pthread_mutex_lock(&turno);
        pthread_mutex_lock(&lock_a);
        nla++;
        if(nla==1) {
            pthread_mutex_lock(&lock_b);
        }
        pthread_mutex_unlock(&lock_a);
        pthread_mutex_unlock(&turno);
        printf("macacoA%d: Estou passando\n", id);
        sleep(2);
        printf("macacoA%d: Terminei de passar\n", id);
        pthread_mutex_lock(&lock_a);
        nla--;
        if(nla==0) {
            pthread_mutex_unlock(&lock_b);
        }
        pthread_mutex_unlock(&lock_a);
        sleep(2);

    }
}

void * ladoB(void * arg){
    int id = *((int *) arg);
    while (1) {

        pthread_mutex_lock(&turno);
        pthread_mutex_lock(&lock_b);
        nlb++;
        if(nlb==1) {
            pthread_mutex_lock(&lock_a);
        }
        pthread_mutex_unlock(&lock_b);
        pthread_mutex_unlock(&turno);
        printf("macacoB%d: Estou passando\n", id);
        sleep(2);
        printf("macacoB%d: Terminei de passar\n", id);
        pthread_mutex_lock(&lock_b);
        nlb--;
        if(nlb==0) {
            pthread_mutex_unlock(&lock_a);
        }
        pthread_mutex_unlock(&lock_b);
        sleep(2);
   }

}
int main(int argc, char const *argv[]) {
    pthread_t a[AV];
    pthread_t b[AV];
    int i;
    int *id;
    for (i = 0; i < AV ; i++) {
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&a[i], NULL, ladoA, (void *) (id));
    }
    for (i = 0; i < AV ; i++) {
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&b[i], NULL, ladoB, (void *) (id));
    }

    pthread_join(a[0],NULL);
    pthread_join(b[0],NULL);
    return 0;
}
