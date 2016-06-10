#include <ncurses.h>
#include <stdlib.h>
#include "Placar.h"

struct tipomatriz{
int ocupado;
int pardecor;
char caracter;
};
typedef struct tipomatriz Tipomatriz;

struct tela{
Tipomatriz matriz_gui[15][25];
};
typedef struct tela Tela;

WINDOW* cria_nova_janela(int alt, int larg, int starty, int startx);

void destroi_janela(WINDOW* janela_local);

Tela* cria_tela();

int mostra_tela(Tela* t);//Mudei o retorno de void para int para poder fazer os testes

int mostra_tela_inicial();

int mostra_tela_final(int pont);

int mostra_tela_placar(int pont);
