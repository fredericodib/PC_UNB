#include "comida.h"

#define COMIDAS 26

Comida comidas[COMIDAS];

void inicializa_comidas() {
  comidas[0].id = 0;
  strcpy(comidas[0].nome, "Espetinnho de Rato");
  comidas[0].valor = -5;
  comidas[0].quantidade = 2;
   
  comidas[1].id = 1;
  strcpy(comidas[1].nome, "Ensopado de melancia");
  comidas[1].valor = 15;
  comidas[1].quantidade = 2;
   
  comidas[2].id = 2;
  strcpy(comidas[2].nome, "Lazanha");
  comidas[2].valor = 60;
  comidas[2].quantidade = 2;
   
  comidas[3].id = 3;
  strcpy(comidas[3].nome, "Peixe do RU");
  comidas[3].valor = -80;
  comidas[3].quantidade = 2;
   
  comidas[4].id = 4;
  strcpy(comidas[4].nome, "sushi");
  comidas[4].valor = 40;
  comidas[4].quantidade = 2;
   
  comidas[5].id = 5;
  strcpy(comidas[5].nome, "sushi chique");
  comidas[5].valor = 60;
  comidas[5].quantidade = 1;
   
  comidas[6].id = 6;
  strcpy(comidas[6].nome, "Carré");
  comidas[6].valor = -40;
  comidas[6].quantidade = 2;
   
  comidas[7].id = 7;
  strcpy(comidas[7].nome, "Pele com frango");
  comidas[7].valor = -10;
  comidas[7].quantidade = 2;
   
  comidas[8].id = 8;
  strcpy(comidas[8].nome, "RU por R$ 2,50");
  comidas[8].valor = 55;
  comidas[8].quantidade = 2;
   
  comidas[9].id = 9;
  strcpy(comidas[9].nome, "Monster");
  comidas[9].valor = 30;
  comidas[9].quantidade = 2;
   
  comidas[10].id = 10;
  strcpy(comidas[10].nome, "maça");
  comidas[10].valor = 15;
  comidas[10].quantidade = 2;
   
  comidas[11].id = 11;
  strcpy(comidas[11].nome, "Melancia");
  comidas[11].valor = 45;
  comidas[11].quantidade = 2;
   
  comidas[12].id = 12;
  strcpy(comidas[12].nome, "Dragon Fruit");
  comidas[12].valor = 100;
  comidas[12].quantidade = 1;
   
  comidas[13].id = 13;
  strcpy(comidas[13].nome, "Barra de chocolate");
  comidas[13].valor = 35;
  comidas[13].quantidade = 2;
   
  comidas[14].id = 14;
  strcpy(comidas[14].nome, "Cachupa Rica RU");
  comidas[14].valor = 39;
  comidas[14].quantidade = 2;
   
  comidas[15].id = 15;
  strcpy(comidas[15].nome, "Marmita da FT");
  comidas[15].valor = 39;
  comidas[15].quantidade = 2;
   
  comidas[16].id = 16;
  strcpy(comidas[16].nome, "2 Pasteis + um suco");
  comidas[16].valor = 50;
  comidas[16].quantidade = 2;
   
  comidas[16].id = 16;
  strcpy(comidas[16].nome, "Docinho da frente do RU");
  comidas[16].valor = 15;
  comidas[16].quantidade = 2;
   
  comidas[17].id = 17;
  strcpy(comidas[17].nome, "Feijoada RU");
  comidas[17].valor = 40;
  comidas[17].quantidade = 2;
   
  comidas[18].id = 18;
  strcpy(comidas[18].nome, "Fricasse RU");
  comidas[18].valor = 40;
  comidas[18].quantidade = 2;
   
  comidas[19].id = 19;
  strcpy(comidas[19].nome, "sushi estragado");
  comidas[19].valor = -60;
  comidas[19].quantidade = 2;
   
  comidas[20].id = 20;
  strcpy(comidas[20].nome, "Yogurte fora da validade");
  comidas[20].valor = -30;
  comidas[20].quantidade = 2;
   
  comidas[21].id = 21;
  strcpy(comidas[21].nome, "Café");
  comidas[21].valor = 35;
  comidas[21].quantidade = 2;
   
  comidas[22].id = 22;
  strcpy(comidas[22].nome, "Hamburguer");
  comidas[22].valor = 50;
  comidas[22].quantidade = 2;
  
  comidas[23].id = 23;
  strcpy(comidas[23].nome, "Bolinho envenenado");
  comidas[23].valor = -150;
  comidas[23].quantidade = 1;

  comidas[24].id = 24;
  strcpy(comidas[24].nome, "Elixir da vida");
  comidas[24].valor = 150;
  comidas[24].quantidade = 1;

  comidas[25].id = 25;
  strcpy(comidas[25].nome, "Suco de maracujá");
  comidas[25].valor = 100;
  comidas[25].quantidade = 1;
}