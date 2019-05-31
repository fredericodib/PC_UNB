#include "arma.h"

#define ARMAS 22

Arma armas[ARMAS];

void inicializa_armas() {
  armas[0].id = 0;
  strcpy(armas[0].nome, "Palmada");
  armas[0].ataque = 5;
  armas[0].quantidade = 0;
 
  armas[1].id = 1;
  strcpy(armas[1].nome, "Espetinho de rato");
  armas[1].ataque = 6;
  armas[1].quantidade = 3;
 
  armas[2].id = 2;
  strcpy(armas[2].nome, "light pexera");
  armas[2].ataque = 25;
  armas[2].quantidade = 3;
 
  armas[3].id = 3;
  strcpy(armas[3].nome, "Meia Falta");
  armas[3].ataque = 83;
  armas[3].quantidade = 1;
 
  armas[4].id = 4;
  strcpy(armas[4].nome, "Spoilers");
  armas[4].ataque = 70;
  armas[4].quantidade = 1;
 
  armas[5].id = 5;
  strcpy(armas[5].nome, "Trabalho para amanhã");
  armas[5].ataque = 50;
  armas[5].quantidade = 2;
 
  armas[6].id = 6;
  strcpy(armas[6].nome, "Faca");
  armas[6].ataque = 15;
  armas[6].quantidade = 3;

  armas[7].id = 7;
  strcpy(armas[7].nome, "Espada samurai");
  armas[7].ataque = 35;
  armas[7].quantidade = 2;
 
  armas[8].id = 8;
  strcpy(armas[8].nome, "Pistola");
  armas[8].ataque = 40;
  armas[8].quantidade = 2;
 
  armas[9].id = 9;
  strcpy(armas[9].nome, "Prova automatos");
  armas[9].ataque = 90;
  armas[9].quantidade = 1;
 
  armas[10].id = 10;
  strcpy(armas[10].nome, "Metralhadora");
  armas[10].ataque = 50;
  armas[10].quantidade = 2;
 
  armas[11].id = 11;
  strcpy(armas[11].nome, "Bazuka");
  armas[11].ataque = 70;
  armas[11].quantidade = 1;
 
  armas[12].id = 12;
  strcpy(armas[12].nome, "Havaiana de pau");
  armas[12].ataque = 60;
  armas[12].quantidade = 1;
 
  armas[13].id = 13;
  strcpy(armas[13].nome, "Garrafinha de agua");
  armas[13].ataque = 9;
  armas[13].quantidade = 2;
 
  armas[14].id = 14;
  strcpy(armas[14].nome, "Caneta e lapis");
  armas[14].ataque = 9;
  armas[14].quantidade = 2;
 
  armas[15].id = 15;
  strcpy(armas[15].nome, "más noticias");
  armas[15].ataque = 24;
  armas[15].quantidade = 2;
 
  armas[16].id = 16;
  strcpy(armas[16].nome, "Tijolo");
  armas[16].ataque = 12;
  armas[16].quantidade = 2;
 
  armas[17].id = 17;
  strcpy(armas[17].nome, "Notebook");
  armas[17].ataque = 11;
  armas[17].quantidade = 2;
 
  armas[18].id = 18;
  strcpy(armas[18].nome, "Playmobil");
  armas[18].ataque = 13;
  armas[18].quantidade = 2;
 
  armas[19].id = 19;
  strcpy(armas[19].nome, "Taco de basebol");
  armas[19].ataque = 18;
  armas[19].quantidade = 2;
 
  armas[20].id = 20;
  strcpy(armas[20].nome, "Serra eletrica");
  armas[20].ataque = 55;
  armas[20].quantidade = 1; 

  armas[21].id = 21;
  strcpy(armas[21].nome, "Focatia(arma)");
  armas[21].ataque = 85;
  armas[21].quantidade = 1; 
}