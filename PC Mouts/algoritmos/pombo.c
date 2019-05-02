#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"

#define TRUE 1

#define NU 30 
#define CARTAS 10 

sem_t mutex; 
sem_t enchendo;
sem_t cheia;                       
int contador = 0;                     

void * pombo(void *arg);
void * usuario(void *arg);

int main() {
	sem_init(&mutex, 0, 1);
	sem_init(&cheia, 0, 0);
	sem_init(&enchendo, 0, CARTAS);
	pthread_t r[NU];
	pthread_t p;

	int i;
        int *id;
        pthread_create(&p, NULL, pombo, NULL);    
    	for (i = 0; i < NU ; i++) {
            id = (int *) malloc(sizeof(int));
            *id = i;
	    pthread_create(&r[i], NULL, usuario, (void*) id);
	}

	

	pthread_join(p, NULL);
        
	return 0;
}

void* usuario(void *arg) {
	int i = *((int *) arg);
//        printf("usuario\n");
	while(TRUE) {             
		 sem_wait(&enchendo); 
		 sem_wait(&mutex);
		 contador++;
		 printf("Usuário %d colocou uma carta na mochila do pombo.\n",i);
		 sleep(1);

		 if (contador == CARTAS) {        
		     sem_post(&cheia);   
		 }

		 sem_post(&mutex);
	}
        pthread_exit(0);
}

void* pombo(void *arg) {
	
	while(TRUE) {
		 sem_wait(&cheia);
		 sem_wait(&mutex);
	         printf("Pombo levando as cartas.\n");
                 sleep(1);
		 contador = 0;
		 int i = 0;
                 
	         printf("Pombo voltou.\n");
		  i = 0;
                 for(i = 0; i < CARTAS;i++){
			sem_post(&enchendo);
		 }
		 sem_post(&mutex);
	}
        pthread_exit(0);
}
