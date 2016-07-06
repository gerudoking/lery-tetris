#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define MAX_PLACAR 5

struct tipojogador{
  char nome[6];
  int pontos;
};
typedef struct tipojogador Jogador;

int cria_placar(void);

int atualiza_placar(int pontuacao);

int mostra_placar(void);
