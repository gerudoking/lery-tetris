#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define MAX_PLACAR 5

struct tipojogador{
  char nome[6];
  int pontos;
};
typedef struct tipojogador Jogador;

/**
 * Para esta função, foi utilizado o seguinte critério de teste:
 * Caso a função retorne 0, sua execução foi bem sucedida e rodou
 * até o final. Caso contrário, houve algum erro.
*/
int cria_placar(void);

/**
 * Para esta função, foram utilizados os seguintes critérios de teste:
 * Caso a função retorne 0, foi bem sucedida. Porém, se retornar 1, significa
 * que o arquivo de placar não existe. Caso retorne 2, houve falha ao escrever
 * no arquivo. Se retornar 3, a pontuação que está sendo escrita no arquivo
 * é maior que o limite máximo de pontos (99999).
*/
int atualiza_placar(int pontuacao);

/**
 * Para esta função, foram utilizados os seguintes critérios de teste:
 * Caso a função retorne 0, foi bem sucedida. Porém, se retornar 1, significa
 * que o arquivo de placar não existe. Caso retorne 2, o arquivo está vazio,
 * logo o placar não podendo ser mostrado.
*/
int mostra_placar(void);
