/*
    Aluno: Frederico Pinheiro Dib
    Matricula: 15/0125925
    Estudo Dirigido 3
*/

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"

#define M 10
#define GORILA_A 1
#define GORILA_B 1

pthread_mutex_t turno;
pthread_mutex_t mutex_a;
pthread_mutex_t mutex_b;
pthread_mutex_t entrada;

int a = 0;
int b = 0;

void *montain_a(void *arg);
void *montain_b(void *arg);
void pass_a(int);
void pass_b(int);
void *gorila_a(void *arg);
void *gorila_b(void *arg);

int main()
{
    pthread_mutex_init(&mutex_a, NULL);
    pthread_mutex_init(&mutex_b, NULL);
    pthread_mutex_init(&turno, NULL);
    pthread_mutex_init(&entrada, NULL);

    pthread_t r[M];
    pthread_t ga[GORILA_A];
    pthread_t gb[GORILA_B];

    int i;
    int *id;
    for (i = 0; i < M; i++)
    {
        id = (int *)malloc(sizeof(int));
        *id = i;
        if (i % 2 == 0)
        {
            pthread_create(&r[i], NULL, montain_a, (void *)(id));
        }
        else
        {
            pthread_create(&r[i], NULL, montain_b, (void *)(id));
        }
    }

    for (i = 0; i < GORILA_A; i++)
    {
        id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&ga[i], NULL, gorila_a, (void *)(id));
    }

    for (i = 0; i < GORILA_B; i++)
    {
        id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&gb[i], NULL, gorila_b, (void *)(id));
    }

    for (i = 0; i < M; i++)
    {
        if (pthread_join(r[i], NULL))
        {
            printf("Could not join thread %d\n", i);
            return -1;
        }
    }

    for (i = 0; i < GORILA_A; i++)
    {
        if (pthread_join(ga[i], NULL))
        {
            printf("Could not join thread %d\n", i);
            return -1;
        }
    }

    for (i = 0; i < GORILA_B; i++)
    {
        if (pthread_join(gb[i], NULL))
        {
            printf("Could not join thread %d\n", i);
            return -1;
        }
    }
    return 0;
}

void *montain_a(void *arg)
{
    int i = *((int *)arg);
    while (1)
    {
        pthread_mutex_lock(&turno);
        pthread_mutex_lock(&mutex_a);
        a = a + 1;
        if (a == 1)
        {
            pthread_mutex_lock(&entrada);
            printf("\nMacacos na montanha A atravessam\n");
        }
        pthread_mutex_unlock(&mutex_a);
        pthread_mutex_unlock(&turno);
        pass_a(i);
        pthread_mutex_lock(&mutex_a);
        a = a - 1;
        printf("Macado %d termina a passar de A para B\n", i);
        if (a == 0)
        {
            printf("Macacos na montanha A param de atravessar\n");
            pthread_mutex_unlock(&entrada);
        }
        pthread_mutex_unlock(&mutex_a);
    }
    pthread_exit(0);
}

void *montain_b(void *arg)
{
    int i = *((int *)arg);
    while (1)
    {
        pthread_mutex_lock(&turno);
        pthread_mutex_lock(&mutex_b);
        b = b + 1;

        if (b == 1)
        {
            pthread_mutex_lock(&entrada);
            printf("\nMacacos na montanha B atravessam\n");
        }
        pthread_mutex_unlock(&mutex_b);
        pthread_mutex_unlock(&turno);
        pass_b(i);
        pthread_mutex_lock(&mutex_b);
        b = b - 1;
        printf("Macado %d termina a passar de B para A\n", i);
        if (b == 0)
        {
            printf("Macacos na montanha B param de atravessar\n");
            pthread_mutex_unlock(&entrada);
        }
        pthread_mutex_unlock(&mutex_b);
    }
    pthread_exit(0);
}

void *gorila_a(void *arg)
{
    sleep(rand() % 3);
    while (1)
    {
        pthread_mutex_lock(&turno);
        printf("\nGorila chegou, ninguem mais entra!\n");
        pthread_mutex_lock(&entrada);
        printf("Gorila comeca a passar de A para B\n");
        sleep(rand() % 2);
        printf("Gorila termina a passar de A para B\n");
        pthread_mutex_unlock(&entrada);
        pthread_mutex_unlock(&turno);
        sleep(5);
    }
    pthread_exit(0);
}

void *gorila_b(void *arg)
{
    sleep(rand() % 3);
    while (1)
    {
        pthread_mutex_lock(&turno);
        printf("\nGorila chegou, ninguem mais entra!\n");
        pthread_mutex_lock(&entrada);
        printf("Gorila comeca a passar de B para A\n");
        sleep(rand() % 2);
        printf("Gorila termina a passar de B para A\n");
        pthread_mutex_unlock(&entrada);
        pthread_mutex_unlock(&turno);
        sleep(5);
    }
    pthread_exit(0);
}

void pass_b(int i)
{
    printf("Macado %d comeca a passar de B para A\n", i);
    sleep(rand() % 2);
}

void pass_a(int i)
{
    printf("Macado %d comeca a passar de A para B\n", i);
    sleep(rand() % 2);
}
