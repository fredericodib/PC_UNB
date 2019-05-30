/*

ALUNO: FREDERICO PINHEIRO DIB - 15/0125925
PROFESSOR: ALCHIERI
ESTUDO DIRIGIDO 13 - abcd - 1/2019

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
/*#include "pthread_barrier.c"*/

#define PAC 10  
#define PBD 5   
#define TRUE 1   

pthread_barrier_t barrier;  

void * func_pac(void *arg) {
   printf("A");
   pthread_barrier_wait(&barrier); 
   pthread_barrier_wait(&barrier); 
   printf("C"); 
   pthread_barrier_wait(&barrier); 
   pthread_barrier_wait(&barrier);
}



void * func_pbd(void *arg) {
   pthread_barrier_wait(&barrier);
   printf("B");
   pthread_barrier_wait(&barrier); 
   pthread_barrier_wait(&barrier); 
   printf("D");
   pthread_barrier_wait(&barrier); 
}


int main(int argc, char *argv[]) {
  
  pthread_t pacId[PAC];
  pthread_t pbdId[PBD];

  pthread_barrier_init(&barrier, NULL, PAC+PBD);


  int * id;
  int i;
  for (i = 0; i < PAC; i++){
     id = (int *) malloc(sizeof(int));
     *id = i;
     pthread_create(&pacId[i], NULL, func_pac, (void *) (id));

  }



  for (i = 0; i < PBD; i++){
     id = (int *) malloc(sizeof(int));
     *id = i;
     pthread_create(&pbdId[i], NULL, func_pbd, (void *) (id));

  }


  for (i = 0; i < PAC; i++){
       if(pthread_join(pacId[i], NULL)){
          exit(1);
       }
  }


  for (i = 0; i < PBD; i++){
       if(pthread_join(pbdId[i], NULL)){
          exit(1);
       }
  }
}


