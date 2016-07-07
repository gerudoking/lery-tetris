#include "Tela.h"

typedef struct peca{
int posicao_x, posicao_y,tamanho,orientacao,cor,tipo;
char* simbolo;
char formato[7][7];
}peca;

peca* nova_peca(Tela* tela);

int move_peca_x(Tela* tela,peca* a,int direcao);

int move_peca_y(Tela* tela,peca* a);

void rotaciona_peca(Tela* tela,peca* a);
