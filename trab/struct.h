typedef struct arma {
  int id;
  int ataque;
  char nome[30];
  int quantidade;
} Arma;

typedef struct comida {
  int id;
  int valor;
  char nome[30];
  int quantidade;
} Comida;

typedef struct jogador {
  int id;
  int vida;
  char nome[30];
  Arma arma;
} Jogador;