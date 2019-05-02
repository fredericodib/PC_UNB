#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"

#define AV 4

pthread_mutex_t lock_ler = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_escreve = PTHREAD_MUTEX_INITIALIZER;
int nl=0;

void  * leitura(void * arg) {
    int id = *((int *) arg);
    while (1) {
        pthread_mutex_lock(&lock_ler);
        nl++;
        if(nl==1) {
        pthread_mutex_lock(&lock_escreve);
        }
        pthread_mutex_unlock(&lock_ler);
        printf("Leitor%d: Estou lendo\n", id);
        sleep(2);
        printf("Leitor%d: Terminei de ler\n", id);
        pthread_mutex_lock(&lock_ler);
        nl--;
        if(nl==0) {
        pthread_mutex_unlock(&lock_escreve);
        }
        pthread_mutex_unlock(&lock_ler);
        sleep(2);
    }

}

void  * escreve(void * arg) {
  int id = *((int *) arg);

    while (1) {
        sleep(1);
        pthread_mutex_lock(&lock_escreve);
        printf("Escritor%d: Estou escrevendo\n", id);
        sleep(2);
        printf("Escritor%d: Terminei de escrever\n", id);
        pthread_mutex_unlock(&lock_escreve);
    }

}

int main() {
    pthread_t a[AV];
    pthread_t b[AV];
    int i;
    int *id;
    for (i = 0; i < AV ; i++) {
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&a[i], NULL, leitura, (void *) (id));
    }
    for (i = 0; i < AV ; i++) {
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&b[i], NULL, escreve, (void *) (id));
    }

    pthread_join(a[0],NULL);
    pthread_join(b[0],NULL);

    return 0;
}
