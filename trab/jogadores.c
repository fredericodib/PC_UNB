#include "jogadores.h"

#define NOMES 64
#define JOGADORES 10

char nome[NOMES][30];
Jogador jogadores[JOGADORES];

void inicializa_nomes() {
  strcpy(nome[0], "Mouts");
  strcpy(nome[1], "Fred");
  strcpy(nome[2], "Fredysney");
  strcpy(nome[3], "Vidal");
  strcpy(nome[4], "Lucero");
  strcpy(nome[5], "Turing");
  strcpy(nome[6], "Khalil");
  strcpy(nome[7], "Nicholas");
  strcpy(nome[8], "Nichobolas");
  strcpy(nome[9], "Mafra");
  strcpy(nome[10], "Marcola");
  strcpy(nome[11], "Amanda");
  strcpy(nome[12], "Amandinha");
  strcpy(nome[13], "Vasco");
  strcpy(nome[14], "Tuts");
  strcpy(nome[15], "Novo_Tuts");
  strcpy(nome[16], "Thiaguinho");
  strcpy(nome[17], "Davisão");
  strcpy(nome[18], "Cris");
  strcpy(nome[19], "Carla");
  strcpy(nome[20], "Pontes");
  strcpy(nome[21], "Zorrom");
  strcpy(nome[22], "Zorran");
  strcpy(nome[23], "Billy");
  strcpy(nome[24], "Juju");
  strcpy(nome[25], "Six");
  strcpy(nome[26], "Vitinho");
  strcpy(nome[27], "Gabriel");
  strcpy(nome[28], "Lucas");
  strcpy(nome[29], "Igor");
  strcpy(nome[30], "Alchieri");
  strcpy(nome[31], "Bruno");
  strcpy(nome[32], "Brunelder");
  strcpy(nome[33], "Alisson");
  strcpy(nome[34], "Mesquita");
  strcpy(nome[35], "Carolzinha");
  strcpy(nome[36], "Fernanda");
  strcpy(nome[37], "Perotto");
  strcpy(nome[38], "Bob");
  strcpy(nome[39], "Javaescripto");
  strcpy(nome[40], "Rails");
  strcpy(nome[41], "Ruby");
  strcpy(nome[42], "Cafebabe");
  strcpy(nome[43], "Leozinho");
  strcpy(nome[44], "Phelps");
  strcpy(nome[45], "Lalis");
  strcpy(nome[46], "DJ");
  strcpy(nome[47], "Bruna");
  strcpy(nome[48], "Luiza");
  strcpy(nome[49], "Lara");
  strcpy(nome[50], "Soneca");
  strcpy(nome[51], "Diegod");
  strcpy(nome[52], "Porto");
  strcpy(nome[53], "Larissa");
  strcpy(nome[54], "Valentin");
  strcpy(nome[55], "Lamar");
  strcpy(nome[56], "Maquiavel");
  strcpy(nome[57], "BanBan");
  strcpy(nome[58], "Cavral");
  strcpy(nome[59], "Waldomiro");
  strcpy(nome[60], "Rods");
  strcpy(nome[61], "Focatia");
  strcpy(nome[62], "Jussara");
  strcpy(nome[63], "Freduardo");
}

int verifica_nome_repete(int i) {
  int j;
  for(j=i-1;j>0;j--) {
    if (strcmp(jogadores[i].nome, jogadores[j].nome) == 0) {
      return -1;
    }
  }
  return 0;
}

void inicializa_jogadores() {
  int i;
  for (i=0;i<JOGADORES;i++) {
    jogadores[i].id = i;
    jogadores[i].vida = 50;
    strcpy(jogadores[i].nome, nome[rand() % NOMES]);
    jogadores[i].arma.ataque = 5;
    strcpy(jogadores[i].arma.nome, "Palmada");
    while(verifica_nome_repete(i) == -1) {
      strcpy(jogadores[i].nome, nome[rand() % NOMES]);
    }
  }
}

void print_nome_jogadores() {
  int i;
  printf("\033[0;36m");
  for (i=0;i<JOGADORES;i++) {
    printf("%s\n", jogadores[i].nome);
  }
  printf("\033[0m");
  printf("\nAperte ENTER para começar\n");
  getchar();
}