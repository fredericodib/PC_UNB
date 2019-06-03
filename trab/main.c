/*

Aluno: Frederico Pinheiro Dib
Matricula: 15/0125925
PROFESSOR: ALCHIERI
Trabalho 1 - PROGRAMAÇÃO CONCORRENTE - 1/2019

*/

#define TRUE 1
#define BATALHA 1

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "struct.h"
#include "arma.c"
#include "comida.c"
#include "jogadores.c"

pthread_mutex_t p_arma = PTHREAD_MUTEX_INITIALIZER; /* lock pro contador*/
pthread_mutex_t p_comida = PTHREAD_MUTEX_INITIALIZER; /* lock pro contador*/

void procura_arma(int id) {
  int id_arma;
  if ((rand() % 6) == 0) {
    id_arma = (rand() % ARMAS);
    if (armas[id_arma].quantidade > 0) {
      printf("\n\033[0;36m%s\033[0m encontrou \033[0;32m%s\033[0m com %d de dano!\n", jogadores[id].nome, armas[id_arma].nome, armas[id_arma].ataque);
      if (armas[id_arma].ataque > jogadores[id].arma.ataque) {
        armas[id_arma].quantidade--;
        printf("\033[0;36m%s\033[0m pegou \033[0;32m%s\033[0m e larga \033[0;32m%s\033[0m!\n", jogadores[id].nome, armas[id_arma].nome, jogadores[id].arma.nome);
        jogadores[id].arma.ataque = armas[id_arma].ataque;
        strcpy(jogadores[id].arma.nome, armas[id_arma].nome);
      }
      else {
        printf("Porem sua \033[0;32m%s\033[0m é melhor\n", jogadores[id].arma.nome);
      }
    }
  }
}

void procura_comida(int id) {
  int id_comida;
  if ((rand() % 6) == 0) {
    id_comida = (rand() % COMIDAS);
    if (comidas[id_comida].quantidade > 0) {
      printf("\n\033[0;36m%s\033[0m encontrou \033[0;33m%s\033[0m!\n", jogadores[id].nome, comidas[id_comida].nome);
      jogadores[id].vida = jogadores[id].vida + comidas[id_comida].valor;
      comidas[id_comida].quantidade--;
      if (comidas[id_comida].valor > 0) {
        printf("\033[0;36m%s\033[0m ganhou \033[0;31m%d\033[0m de vida!! tendo um total de \033[0;31m%d\033[0m!\n", jogadores[id].nome, comidas[id_comida].valor, jogadores[id].vida);
      }
      else {
        printf("\033[0;36m%s\033[0m perdeu \033[0;31m%d\033[0m de vida!! tendo um total de \033[0;31m%d\033[0m!\n", jogadores[id].nome, comidas[id_comida].valor, jogadores[id].vida);
        if (jogadores[id].vida <= 0) {
          printf("\033[0;36m%s\033[0m morreu!\n", jogadores[id].nome);
        }
      }
    }
  }
}

void verifica_se_vivo_arma(int id) {
  if (jogadores[id].vida <= 0) {
    pthread_mutex_unlock(&p_arma);
    pthread_exit(0);
  }
}

void verifica_se_vivo_comida(int id) {
  if (jogadores[id].vida <= 0) {
    pthread_mutex_unlock(&p_comida);
    pthread_exit(0);
  }
}

int n_vivos() {
  int i, cont=0;
  for (i=0;i<JOGADORES;i++) {
    if (jogadores[i].vida > 0) {
      cont++;
    }
  }
  return cont;
}

void print_vercedor_nome() {
  int i;
  for (i=0;i<JOGADORES;i++) {
    if (jogadores[i].vida > 0) {
      printf("\033[0;36m%s\033[0m venceu o torneio!\n", jogadores[i].nome);
    }
  }
}

void checa_vencedor() {
  int n;
  n = n_vivos();
  if (n == 1) {
    printf("Só existe um jogador vivo!\n");
    print_vercedor_nome();
    exit(0);
  }
  if (n == 0) {
    printf("Todos os jogadores morreram na ilha!\n");
    printf("Todos são otarios! Ninguem venceu!!!\n");
    exit(0);
  }
}

void escolhe_participantes(int * lut_1, int * lut_2) {
  int vivos_n = n_vivos();
  int i=0, j=0;
  int *vetor_vivos;
  vetor_vivos = malloc (vivos_n * sizeof (int));
  for (i=0;i<JOGADORES;i++) {
    if (jogadores[i].vida > 0) {
      vetor_vivos[j] = i;
      j++;
    }
  }
  *lut_1 = vetor_vivos[rand() % vivos_n];
  *lut_2 = vetor_vivos[rand() % vivos_n];
  while (*lut_1 == *lut_2) {
    *lut_2 = vetor_vivos[rand() % vivos_n];
  }
}

void acontece_batalha(int lut_1, int lut_2) {
  while((jogadores[lut_1].vida > 0) && (jogadores[lut_2].vida > 0)) {
    printf("\033[0;36m%s\033[0m ataca com \033[0;31m%d\033[0m\n", jogadores[lut_1].nome, jogadores[lut_1].arma.ataque);
    jogadores[lut_2].vida = jogadores[lut_2].vida - jogadores[lut_1].arma.ataque;
    printf("\033[0;36m%s\033[0m ta com \033[0;31m%d\033[0m de vida\n\n", jogadores[lut_2].nome, jogadores[lut_2].vida);
    if (jogadores[lut_2].vida <= 0) {
      break;
    }
    sleep(1);
    printf("\033[0;36m%s\033[0m ataca com \033[0;31m%d\033[0m\n", jogadores[lut_2].nome, jogadores[lut_2].arma.ataque);
    jogadores[lut_1].vida = jogadores[lut_1].vida - jogadores[lut_2].arma.ataque;
    printf("\033[0;36m%s\033[0m ta com \033[0;31m%d\033[0m de vida\n\n", jogadores[lut_1].nome, jogadores[lut_1].vida);
  }
  if (jogadores[lut_2].vida <= 0) {
    printf("\033[0;36m%s\033[0m morreu!\n", jogadores[lut_2].nome);
    printf("\033[0;36m%s\033[0m Venceu a batalha!\n", jogadores[lut_1].nome);
  }
  if (jogadores[lut_1].vida <= 0) {
    printf("\033[0;36m%s\033[0m morreu!\n", jogadores[lut_1].nome);
    printf("\033[0;36m%s\033[0m Venceu a batalha!\n", jogadores[lut_2].nome);
  }
}

void *batalhas(void *arg) {
  int lut_1, lut_2;
  while(TRUE) {
    sleep((rand() % 3) + 5);

    pthread_mutex_lock(&p_arma);
    pthread_mutex_lock(&p_comida);
    printf("\n\n\n\033[0;31m###############################################\033[0m\n");
    printf("Alarme tocou!! Para tudo!!!\n");
    checa_vencedor();
    printf("\033[0;31m%d\033[0m VIVO!\n", n_vivos());
    printf("Dois guerreiros serão escolhidos de forma aleatoria!\n");
    escolhe_participantes(&lut_1, &lut_2);
    sleep(2);
    printf("\n\033[0;36m%s\033[0m - vida: \033[0;31m%d\033[0m - arma: \033[0;32m%s\033[0m \033[0;31m%d\033[0m\n", jogadores[lut_1].nome, jogadores[lut_1].vida, jogadores[lut_1].arma.nome, jogadores[lut_1].arma.ataque);
    sleep(2);
    printf("\033[0;36m%s\033[0m - vida: \033[0;31m%d\033[0m - arma: \033[0;32m%s\033[0m \033[0;31m%d\033[0m\n\n", jogadores[lut_2].nome, jogadores[lut_2].vida, jogadores[lut_2].arma.nome, jogadores[lut_2].arma.ataque);
    sleep(4);

    acontece_batalha(lut_1, lut_2);

    checa_vencedor();
    printf("\033[0;31m###############################################\033[0m\n");
    pthread_mutex_unlock(&p_comida);
    pthread_mutex_unlock(&p_arma);
  }
  pthread_exit(0);
}

void *jogadores_func(void *arg) {
  int id = *((int*)arg);

  while (TRUE) {

    pthread_mutex_lock(&p_arma);
    verifica_se_vivo_arma(id);
    procura_arma(id);
    pthread_mutex_unlock(&p_arma);

    sleep(rand() % 5);

    pthread_mutex_lock(&p_comida);
    verifica_se_vivo_comida(id);
    procura_comida(id);
    verifica_se_vivo_comida(id);
    pthread_mutex_unlock(&p_comida);

    sleep(rand() % 5);
  }
  pthread_exit(0);
}

int main() {
  srand( (unsigned)time(NULL) );
  system("clear");
  inicializa_nomes();
  inicializa_armas();
  inicializa_comidas();
  inicializa_jogadores();

  print_nome_jogadores();
  system("clear");

  pthread_mutex_init(&p_comida, NULL);
  pthread_mutex_init(&p_arma, NULL);

  pthread_t jogador[JOGADORES], batalha[BATALHA];
  int i;
  int *id;

  for (i = 0; i < JOGADORES; i++) {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&jogador[i], NULL, jogadores_func, (void *)(id));
  }

  for (i = 0; i < BATALHA; i++) {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&batalha[i], NULL, batalhas, (void *)(id));
  }

  for (i = 0; i < JOGADORES; i++) {
    pthread_join(jogador[i], NULL);
  }

  for (i = 0; i < JOGADORES; i++) {
    pthread_join(batalha[0], NULL);
  }

  return 0;
}