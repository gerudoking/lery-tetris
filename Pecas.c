#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "Tela.h"
#include "Tela.c"
typedef struct{
int posicao_x, posicao_y,tamanho,orientacao,cor;
char* simbolo;

}peca;
typedef struct peca peca;

peca* nova_peca(Tela* tela){
	int i;
	peca* a;
	(*a).tamanho=(rand() %3)+3;/*Escolhe um tamanho entre 3 e 5 para a peca*/
	(*a).orientacao=rand() %2;/*Define a orientação: 0 e vertical, 1 e horizontal*/
	(*a).cor=rand() %3;
	(*a).posicao_x=13;
	(*a).posicao_y=6;
		if((*a).orientacao==0){
			for(i=0;i<(*a).tamanho;i++){
				*tela[6+i][13].character="X";
				*tela[6+i][13].ocupado=1;
			}
		}
		else{
			for(i=0;i<(*a).tamanho;i++){
				*tela[6][13+i].character="X";
				*tela[6][13+i].ocupado=1;
			}
		}
	return a;
}

move_peca_x(Tela* tela,peca* a,int x){/*vai receber um inteiro, que vai ser ou -1 ou 1, para mostrar se 
e para mover para a esquerda ou direita, respectivamente*/
	if(x==1){
		(*a).	
	}








}
int main(){

return 0;
}
