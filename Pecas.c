#include <stdlib.h>
#include <time.h>
#include "Pecas.h"

peca* nova_peca(Tela* tela){
	int i;
	peca* a;
	if((*tela).matriz_gui[1][13].ocupado==1) return NULL;
	a=(peca*)malloc(sizeof(peca));
	(*a).tamanho=((rand() %3)+3);/*Escolhe um tamanho entre 3 e 5 para a peca*/
	(*a).tipo=rand() %6;/*Define o tipo de peca: 0 e vertical, 1 e horizontal, 2 e Z, 3 e quadrado, 4 e L, 5 e T*/
	(*a).cor=rand() %3 + 1;
	(*a).posicao_x=10;
	(*a).posicao_y=4;
	switch((*a).tipo){
		case 0:
			for(i=0;i<(*a).tamanho;i++){
				(*a).formato[i][3].caracter='X';
			}
		break;
		
		case 1:
			for(i=0;i<(*a).tamanho;i++){
				(*a).formato[3][i].caracter='X';
			}
		break;

		case 2:/*peca Z*/
			for(i=0;i<3;i++){
				(*a).formato[2+i][3]='X';
				if(i<2){
					(*a).formato[2][i+2]='X';
					(*a).formato[4][i+3]='X';
				}
			}
		break;
		
		case 3:/*quadrado*/
			for(i=0;i<2;i++){
				for(j=0;j<2;j++){
					(*a).formato[j+2][i+2]='X';
				}
			}
		break;
		
		case 4:/*peca L*/
			for(i=0;i<3;i++){
				(*a).formato[2+i][2]='X';
				(*a).formato[4][i+2]='X';
			}
		break;

		case 5:/*peca T*/
			for(i=0;i<5;i++){
				(*a).formato[2][i+1]='X';
				if(i<2) (*a).formato[i+3][3]='X';
			}
		break;
	}
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if((*a).formato[i][j]!='X') (*a).formato[i][j]=' ';
		}
	}
	return a;
}

int move_peca_x(Tela* tela,peca* a,int direcao){/*vai receber um inteiro, que vai ser ou -1 ou 1, para mostrar se e para mover para a esquerda ou direita, respectivamente*/
	int i,j;,
	int x=(*a).posicao_x;
	int y=(*a).posicao_y;
	int Tamanho=(*a).tamanho;
	int cor=(*a).cor;
	x+=direcao;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X' && (*tela).matriz_gui[y+i][x+j].ocupado==1) return 1;
			else if((*a).formato[i][j]=='X') (*tela).matriz_gui[y+i][x+j].character=' ';
		}
	}
	(*a).posicao_x+=direcao;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X') {
				tela.matriz_gui[y+i][x+j].character='X';
				(*tela).matriz_gui[y+i][x+j].pardecor=cor;
			}
		}
	}
	return 0;	
}


int move_peca_y(Tela* tela,peca* a){/*Como so podemos mover para baixo, nao necessitamos de entrada de inteiros*/
	int x=(*a).posicao_x;
	int y=(*a).posicao_y;
	int Tamanho=(*a).tamanho;
	int i,j;
	int cor= (*a).cor;
	
	y++;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X' && (*tela).matriz_gui[y+i][x+j].ocupado==1) return 1;
			else if((*a).formato[i][j]=='X') (*tela).matriz_gui[y+i][x+j].character=' ';
		}
	}
	(*a).posicao_x+=direcao;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X') {
				tela.matriz_gui[y+i][x+j].character='X';
				(*tela).matriz_gui[y+i][x+j].pardecor=cor;
			}
		}
	}
	return 0;
}
