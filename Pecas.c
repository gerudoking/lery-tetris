#include <stdlib.h>
#include <time.h>
#include "Pecas.h"

peca* nova_peca(Tela* tela){
	int i;
	peca* a;
	if((*tela).matriz_gui[1][13].ocupado==1) return NULL;
	a=(peca*)malloc(sizeof(peca));
	(*a).tamanho=((rand() %3)+3);/*Escolhe um tamanho entre 3 e 5 para a peca*/
	(*a).tipo=rand() %6;/*Define o tipo de peca: 0 e vertical, 1 e horizontal, 2 e Z, 3 e T, 4 e quadrado, 5 e L*/
	(*a).cor=rand() %3 + 1;
	(*a).posicao_x=13;
	(*a).posicao_y=3;
	switch((*a).tipo){
		case 0:
			for(i=0;i<(*a).tamanho;i++){
				(*tela).matriz_gui[1+i][13].caracter='X';
			}
		break;
		
		case 1:
			for(i=0;i<(*a).tamanho;i++){
				(*tela).matriz_gui[1][13+i].caracter='X';
			}
		break;

		case 2:/*peca Z*/
			for(i=0;i<3;i++){
				(*a).formato[i][1]='X';
				(*a).formato[2][i+1]='X';
				(*a).formato[2+i][3]='X';
			}
		break;
		
		case 3:/*quadrado*/
			for(i=0;i<2;i++){
				for(j=0;j<2;j++){
					(*a).formato[j+1][i+1]='X';
				}
			}
		break;
		
		case 4:/*peca L*/
			for(i=0;i<4;i++){
				(*a).formato[i][1]='X';
				(*a).formato[3][i+1]='X';
			}
		break;

		case 5:/*peca T*/
			for(i=0;i<5;i++){
				(*a).formato[0][i]='X';
				if(i<3) (*a).formato[i][3]='X';
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
	int i,flag=0,x=(*a).posicao_x,y=(*a).posicao_y,Tamanho=(*a).tamanho,cor=(*a).cor;
		
		switch((*a).tipo){			
			case 0:/*vertical*/
			/*primeiro verificamos se a peca ja 								esta nos extremos da tela. Nesse caso, ela
								nao pode mover*/
			if(direcao==1){/*dependendo da direcao desejada do movimento, checaremos se ha parte de outra peca do lado adequado*/
				if(x==23) return 1;
				for(i=0;i<Tamanho;i++){
					if((*tela).matriz_gui[y+i][x+1].ocupado==1){/*aqui checamos se ha parte de outra peca ao lado da peca ativa. a flag sera usada para sair da funcao caso isso seja verdade*/
						flag=1;
						i=Tamanho;
					}
				}
				if(flag!=0) return 2;/*cada possivel caso de erro tem o seu retorno, permitindo
						acoes de acordo com cada caso*/
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y+i][x].caracter=' ';/*Temos que limpar o lugar que a peca ocupava antes de move-la*/
				}
				((*a).posicao_x)++;/*finalmente, a posicao na struct da peca e mudada*/			x=((*a).posicao_x);
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y+i][x].caracter='X';
					(*tela).matriz_gui[y+i][x].pardecor=cor;
				}
				return 5;
			}

			if(direcao==-1){
				if(x==1) return 1;
				for(i=0;i<Tamanho;i++){
					if((*tela).matriz_gui[y+i][x-1].ocupado==1){
						flag=1;
						i=Tamanho;
					}
				}
				if(flag!=0) return 3;
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y+i][x].caracter=' ';
				}
				((*a).posicao_x)--;/*finalmente, a posicao na struct da peca e mudada*/			x=((*a).posicao_x);
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y+i][x].caracter='X';
					(*tela).matriz_gui[y+i][x].pardecor=cor;
				}
				return 5;
			}
		return 3;/*nesse ponto, se a funcao nao terminou, alguma coisa deu errado*/
		break;
		
		case 1:
			if(direcao==1){
				if(x+Tamanho==24) return 4;
				if((*tela).matriz_gui[y][x+Tamanho].ocupado==1) return 5;/*com pecas horizontais, so precisamos checar 2 posicoes*/
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y][x+i].caracter=' ';
				}
				((*a).posicao_x)++;
				x=((*a).posicao_x);
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y][x+i].caracter='X';
					(*tela).matriz_gui[y][x+i].pardecor=cor;
				}
				return 5;
			}
			if(direcao==-1){
				if(x==1) return 4;
				if((*tela).matriz_gui[y][x-1].ocupado==1) return 6;
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y][x+i].caracter=' ';
				}
				((*a).posicao_x)--;
				x=((*a).posicao_x);
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y][x+i].caracter='X';
					(*tela).matriz_gui[y][x+i].pardecor=cor;
				}
				return 5;	
			}
			return 6;
			break;
		case 3:
		break;

		case 4:
		break;

		case 5:
		break;
		}
return 8;
}


int move_peca_y(Tela* tela,peca* a){/*Como so podemos mover para baixo, nao necessitamos de entrada de inteiros*/
	int x=(*a).posicao_x;
	int y=(*a).posicao_y;
	int Tamanho=(*a).tamanho;
	int i;
	int flag=0;
	int cor= (*a).cor;
	
	if((*a).tipo==0){
		if(y+Tamanho==15) return 1; /*Caso a peca ja esteja no fim da tela, ela nao pode mover*/
		if((*tela).matriz_gui[y+Tamanho][x].ocupado==1) return 2; /*Caso exista parte de uma peca embaixo da peca, ela deve parar*/
		for(i=0;i<Tamanho;i++){
			(*tela).matriz_gui[y+i][x].caracter=' ';
		}
		((*a).posicao_y)+=1;
		y=((*a).posicao_y);
		for(i=0;i<Tamanho;i++){
			(*tela).matriz_gui[y+i][x].caracter='X';
			(*tela).matriz_gui[y+i][x].pardecor=cor;
		}
	return 5;
	}
	
	if((*a).tipo==1){
		if(y==14) return 3;/*teste de encontro com borda da tela*/
		
		for(i=0;i<Tamanho;i++){
			if((*tela).matriz_gui[y+1][x+i].ocupado==1){
				flag=1;
				i=Tamanho;
			}
		}
		if(flag==1) return 4;
		for(i=0;i<Tamanho;i++){
			(*tela).matriz_gui[y][x+i].caracter=' ';
		}
		((*a).posicao_y)+=1;
		y=((*a).posicao_y);
		for(i=0;i<Tamanho;i++){
			(*tela).matriz_gui[y][x+i].caracter='X';
			(*tela).matriz_gui[y][x+i].pardecor=cor;
		}
		return 5;

	}
	return 6;
}
