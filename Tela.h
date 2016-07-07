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

/**
 * Para esta função, foi utilizado o seguinte critério de teste:
 * Caso a tela retornada pela função não seja nula, temos a
 * função como bem sucedida.
*/
Tela* cria_tela();

/**
 * Para esta função, foi utilizado o seguinte critério de teste:
 * Caso a função retorne 0, sua execução foi bem sucedida e rodou
 * até o final. Caso contrário, houve algum erro.
*/
int mostra_tela(Tela* t);//Mudei o retorno de void para int para poder fazer os testes

/**
 * Para esta função, foi utilizado o seguinte critério de teste:
 * Caso a função retorne 0, sua execução foi bem sucedida e rodou
 * até o final. Caso contrário, houve algum erro.
*/
int mostra_tela_inicial();

/**
 * Para esta função, foi utilizado o seguinte critério de teste:
 * Caso a função retorne 0, sua execução foi bem sucedida e rodou
 * até o final. Caso contrário, houve algum erro.
*/
int mostra_tela_final(int pont);

/**
 * Para esta função, foi utilizado o seguinte critério de teste:
 * Caso a função retorne 0, sua execução foi bem sucedida e rodou
 * até o final. Caso contrário, houve algum erro.
*/
int mostra_tela_placar(int pont);
