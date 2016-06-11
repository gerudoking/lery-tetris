#include <stdlib.h>
#include <time.h>
#include "Pecas.h"
peca* nova_peca(Tela* tela){
	int i,j;
	peca* a;
	if((*tela).matriz_gui[1][13].ocupado==1) return NULL;
	a=(peca*)malloc(sizeof(peca));
	(*a).tamanho=((rand() %3)+3);/*Escolhe um tamanho entre 3 e 5 para as pecas vertical e horizontal*/
	(*a).tipo=rand() %6;/*Define o tipo de peca: 0 e vertical, 1 e horizontal, 2 e Z, 3 e quadrado, 4 e L, 5 e T*/
	(*a).cor=rand() %3 + 1;
	(*a).posicao_x=8;
	(*a).posicao_y=0;
	switch((*a).tipo){
		case 0:
			for(i=0;i<(*a).tamanho;i++){
				(*a).formato[i][3]='X';
			}
		break;
		
		case 1:
			for(i=0;i<(*a).tamanho;i++){
				(*a).formato[3][i]='X';
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
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]!='X') (*a).formato[i][j]=' ';
		}
	}
	return a;
}

int move_peca_x(Tela* tela,peca* a,int direcao){/*vai receber um inteiro, que vai ser ou -1 ou 1, para mostrar se e para mover para a esquerda ou direita, respectivamente*/
	int i,j,flag=0;
	int x=(*a).posicao_x;
	int y=(*a).posicao_y;
	int cor=(*a).cor;
	for(i=0;i<7;i++){/*primeiro, limpamos a peca da tela. Isso evita que seja confundida com outras pecas*/
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X'){
				(*tela).matriz_gui[y+j][x+i].ocupado=0;
				(*tela).matriz_gui[y+j][x+i].caracter=' ';
			}
		}
	}
	x+=direcao;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){/*agora, usando a matriz formato, vemos se a peca pode ocupar a posicao desejada*/
			if((*a).formato[i][j]=='X' && (*tela).matriz_gui[y+j][x+i].ocupado==1) flag++;
			if((*a).formato[i][j]=='X' && (x==0 || x==20)) flag++;
		}
	}
	if(flag!=0){/*se for encontrado overlap entre a peca e o resto da tela, a peca e reescrita onde estava, e a funcao para */
	x=(*a).posicao_x;
		for(i=0;i<7;i++){
			for(j=0;j<7;j++){
				if((*a).formato[i][j]=='X'){
					(*tela).matriz_gui[y+j][x+i].ocupado=1;
					(*tela).matriz_gui[y+j][x+i].caracter='X';
				}
			}
		}
	return 8;
	}
	(*a).posicao_x+=direcao;/*se nao houver problema, a coordenada x da peca e alterada, e a peca e escrita em sua nova posicao*/
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X') {
				(*tela).matriz_gui[y+j][x+i].caracter='X';
				(*tela).matriz_gui[y+j][x+i].pardecor=cor;
				(*tela).matriz_gui[y+j][x+i].ocupado=1;
			}
		}
	}
	return 0;	
}


int move_peca_y(Tela* tela,peca* a){/*Como so podemos mover para baixo, nao necessitamos de entrada de inteiros*/
	int x=(*a).posicao_x;
	int y=(*a).posicao_y;
	int i,j,flag=0;
	int cor=(*a).cor;
	

	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X'){
				(*tela).matriz_gui[y+j][x+i].ocupado=0;
				(*tela).matriz_gui[y+j][x+i].caracter=' ';
			}
		}
	}
	y++;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X' && (*tela).matriz_gui[y+j][x+i].ocupado==1) flag++;
			if((*a).formato[i][j]=='X' && y+j==15) flag++;
		}
	}

	if(flag!=0){
	y=(*a).posicao_y;
		for(i=0;i<7;i++){
			for(j=0;j<7;j++){
				if((*a).formato[i][j]=='X'){
					(*tela).matriz_gui[y+j][x+i].ocupado=1;
					(*tela).matriz_gui[y+j][x+i].caracter='X';
				}
			}
		}
	return 1;
	}
	(*a).posicao_y=y;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X') {
				(*tela).matriz_gui[y+j][x+i].caracter='X';
				(*tela).matriz_gui[y+j][x+i].pardecor=cor;
				(*tela).matriz_gui[y+j][x+i].ocupado=1;
			}
		}
	}
	return 8;
}
void rotaciona_peca(Tela* tela,peca* a){
	int i,j,flag=0;
	char compara[7][7];
	char k;
	int x=(*a).posicao_x;
	int y=(*a).posicao_y;
	
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			compara[i][j]=(*a).formato[i][j];
		}	
	}

	for(i=0;i<3;i++){
		for(j=i;j<7-i-1;j++){
			k=compara[i][j];
			compara[i][j]=compara[j][7-1-i];
			compara[j][7-1-i]=compara[7-1-i][7-1-j];
			compara[7-1-i][7-1-j]=compara[7-1-j][i];
			compara[7-1-j][i]=k;
		}	
	}
	
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X'){
				(*tela).matriz_gui[y+j][x+i].ocupado=0;
				(*tela).matriz_gui[y+j][x+i].caracter=' ';
			}
		}
	}	
	
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if(compara[i][j]=='X' && (*tela).matriz_gui[y+i][x+j].ocupado==1) flag++;
		}
	}

	if(flag!=0){
		for(i=0;i<7;i++){
			for(j=0;j<7;j++){
				if((*a).formato[i][j]=='X'){
					(*tela).matriz_gui[y+j][x+i].ocupado=1;
					(*tela).matriz_gui[y+j][x+i].caracter='X';
				}
			}
		}
	return;
	}	

	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			(*a).formato[i][j]=compara[i][j];
		}
	}
	
}

