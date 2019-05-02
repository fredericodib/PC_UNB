#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"

#define MOD_AC 10
#define MOD_BD 10

pthread_barrier_t barrier_AC;
pthread_barrier_t barrier_BD;

int num_mod = MOD_AC + MOD_BD;

void * P_AC (void * arg) {
    int id = *((int *) arg);

    printf("A");
    pthread_barrier_wait(&barrier_AC);
    pthread_barrier_wait(&barrier_BD);
    printf("C");
    pthread_barrier_wait(&barrier_AC);

    pthread_exit(0);

}

void * P_BD (void * arg) {

    int id = *((int *) arg);

    pthread_barrier_wait(&barrier_AC);
    printf("B");
    pthread_barrier_wait(&barrier_BD);
    pthread_barrier_wait(&barrier_AC);
    printf("D");

    pthread_exit(0);

}


int main() {
    int i, j;
    pthread_t AC[100];
    pthread_t BD[100];
    pthread_barrier_init(&barrier_AC, NULL, num_mod);
    pthread_barrier_init(&barrier_BD, NULL, num_mod);
    int * id;

    for (i = 0; i < MOD_AC; i++){
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&AC[i], NULL, P_AC, (void *) (id));
    }
    for (i = 0; i < MOD_BD; i++){
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&BD[i], NULL, P_BD, (void *) (id));
    }
    for (i = 0; i < MOD_AC; i++) {
        pthread_join(AC[i],NULL);
    }
    for (i = 0; i < MOD_BD; i++) {
        pthread_join(BD[i],NULL);
    }
    printf("\n");

    return 0;
}
