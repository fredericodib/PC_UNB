#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
 
int main(void) {
   int i = 10;
 
   fork();
   i++;
   fork();
   i++;
   printf("Valor de i para o processo %d: %d\n",getpid(),i);
   
   return 0;
}
