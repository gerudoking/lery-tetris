#include <stdlib.h>
#include <time.h>
#include "Pecas.h"
#include "Tela.h"
peca* nova_peca(Tela* tela){
	int i;
	peca* a;
	a=(peca*)malloc(sizeof(peca));
	(*a).tamanho=((rand() %3)+3);/*Escolhe um tamanho entre 3 e 5 para a peca*/
	(*a).orientacao=1; /*rand() %2;Define a orientação: 0 e vertical, 1 e horizontal*/
	(*a).cor=rand() %3;
	(*a).posicao_x=13;
	(*a).posicao_y=1;
		if((*a).orientacao==0){
			for(i=0;i<(*a).tamanho;i++){
				(*tela).matriz_gui[1+i][13].caracter='X';
			}
		}
		else{
			for(i=0;i<(*a).tamanho;i++){
				(*tela).matriz_gui[1][13+i].caracter='X';
			}
		}
	return a;
}

int move_peca_x(Tela* tela,peca* a,int direcao){/*vai receber um inteiro, que vai ser ou -1 ou 1, para mostrar se e para mover para a esquerda ou direita, respectivamente*/
	int i,flag=0,x=(*a).posicao_x,y=(*a).posicao_y,Tamanho=(*a).tamanho;
		if((*a).orientacao==0){/*dependendo da orientacao da peca(vertical ou horizontal), agiremos diferentemente*/
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
				}
				return 5;
			}
		return 3;/*nesse ponto, se a funcao nao terminou, alguma coisa deu errado*/
		}
		if((*a).orientacao==1){
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
				}
				return 5;	
			}
			return 6;
		}
return 8;
}


int move_peca_y(Tela* tela,peca* a){/*Como so podemos mover para baixo, nao necessitamos de entrada de inteiros*/
	int x=(*a).posicao_x,y=(*a).posicao_y,Tamanho=(*a).tamanho,i,flag=0;
	if((*a).orientacao==0){
		if(y+Tamanho==15) return 1; /*Caso a peca ja esteja no fim da tela, ela nao pode mover*/
		if((*tela).matriz_gui[y+Tamanho+1][x].ocupado==1) return 2; /*Caso exista parte de uma peca embaixo da peca, ela deve parar*/
		for(i=0;i<Tamanho;i++){
			(*tela).matriz_gui[y+i][x].caracter=' ';
		}
		((*a).posicao_y)+=1;
		y=((*a).posicao_y);
		for(i=0;i<Tamanho;i++){
			(*tela).matriz_gui[y+i][x].caracter='X';
		}
	return 5;
	}
	
	if((*a).orientacao==1){
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
		}
		return 5;
	}
	return 6;
}
