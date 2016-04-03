#include <ncurses.h>

typedef struct tipomatriz{
int ocupado;
int pardecor;
char caracter;
};
typedef struct tipomatriz Tipomatriz;

typedef struct tela{
Tipomatriz matriz_gui[15][25];
};
typedef struct tela Tela;

Tela* cria_tela();

int mostra_tela(Tela* t);//Mudei o retorno de void para int para poder fazer os testes
