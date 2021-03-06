#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"

pthread_barrier_t barrier;
int num_linhas = 100;
int matriz[100][100];
int sum_vet[100];
int sum_mat = 0;

void * soma_linhas(void * args){
    int id = *(int *)(args);
    int i;
    sum_vet[id] = 0;
    for(i=0; i < num_linhas;i++){
        sum_vet[id] += matriz[id][i];
    }
    printf("thread %d esperando na barreira \n", id);
    pthread_barrier_wait(&barrier);
    if (id == 0) {
        printf("A barreira foi liberada a thread 0 somará a soma das linhas\n");
        sleep(2);
        for (i = 0; i < num_linhas; i++) {
            sum_mat = sum_mat + sum_vet[i];
        }
        printf("Total da soma: %d\n", sum_mat);
    }

}


int main() {
    int i, j;
    pthread_t threads[100];
    pthread_barrier_init(&barrier, NULL, num_linhas);
    int * id;

    for (i=0;i< num_linhas;i++) {
        for (j = 0; j < num_linhas; j++) {
            matriz[i][j] = 1;
        }
    }

    for (i = 0; i < num_linhas; i++){
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, soma_linhas, (void *) (id));

    }
    for (i = 0; i < num_linhas; i++) {
        pthread_join(threads[i],NULL);
    }
    return 0;
}
