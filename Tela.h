#include <ncurses.h>

typedef struct tipomatriz{
  int ocupado = 0;
};
typedef struct tipomatriz Tipomatriz;

typedef struct tela{
  Tipomatriz matriz_interface[15][25];
  char matriz_gui[30][30];
};
typedef struct tela Tela;

Tela* cria_tela();

int mostra_tela(Tela* t);//Mudei o retorno de void para int para poder fazer os testes
