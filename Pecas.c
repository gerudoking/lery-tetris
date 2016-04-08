#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "Tela.c"
#include "Pecas.h"

peca* nova_peca(Tela* tela){
	int i;
	peca* a;
	(*a).tamanho=((rand() %3)+3);/*Escolhe um tamanho entre 3 e 5 para a peca*/
	(*a).orientacao=rand() %2;/*Define a orientação: 0 e vertical, 1 e horizontal*/
	(*a).cor=rand() %3;
	(*a).posicao_x=13;
	(*a).posicao_y=6;
		if((*a).orientacao==0){
			for(i=0;i<(*a).tamanho;i++){
				(*tela).matriz_gui[6+i][13].caracter="X";
				(*tela).matriz_gui[6+i][13].ocupado=1;
			}
		}
		else{
			for(i=0;i<(*a).tamanho;i++){
				(*tela).matriz_gui[6][13+i].caracter="X";
				(*tela).matriz_gui[6][13+i].ocupado=1;
			}
		}
	return a;
}

int move_peca_x(Tela* tela,peca* a,int direcao){/*vai receber um inteiro, que vai ser ou -1 ou 1, para mostrar se e para mover para a esquerda ou direita, respectivamente*/
	int i,flag=0,x=(*a).posicao_x,y=(*a).posicao_y,Tamanho=(*a).tamanho;
		if((*a).orientacao==0){/*dependendo da orientacao da peca(vertical ou horizontal), agiremos diferentemente*/
			if(x==0 || x==24) return 1;/*primeiro verificamos se a peca ja 								esta nos extremos da tela. Nesse caso, ela
								nao pode mover*/
			for(i=0;i<Tamanho;i++){
				if((*tela).matriz_gui[y+i][x+1].ocupado==1 || (*tela).matriz_gui[y+i][x-1].ocupado==1){/*aqui checamos se ha parte de outra peca ao lado da peca ativa. a flag sera usada para sair da funcao caso isso seja verdade*/
					flag=1;
					i=Tamanho;
				}
			}
			if(flag!=0) return 2;/*cada possivel caso de erro tem o seu retorno, permitindo
						acoes de acordo com cada caso*/
			if(direcao==1){
				((*a).posicao_x)++;/*finalmente, a posicao na struct da peca e mudada*/
				return 0;
			}
			if(direcao==-1){
				((*a).posicao_x)--;
				return 0;	
			}
		return 3;/*nesse ponto, se a funcao nao terminou, alguma coisa deu errado*/
		}
		if((*a).orientacao==1){
			if(x==0 || x+Tamanho==24) return 4;
			
			if((*tela).matriz_gui[y][x-1].ocupado==1 || (*tela).matriz_gui[y][x+Tamanho].ocupado==1) return 5;/*com pecas horizontais, so precisamos checar 2 posicoes*/
			if(direcao==1){
				((*a).posicao_x)++;
				return 0;
			}
			if(direcao==-1){
				((*a).posicao_x)--;
				return 0;	
			}
			return 6;
		}
}


int move_peca_y(Tela* tela,peca* a){/*Como so podemos mover para baixo, nao necessitamos de entrada de inteiros*/
	int x=(*a).posicao_x,y=(*a).posicao_y,Tamanho=(*a).tamanho,i,flag=0;
	if((*a).orientacao==0){
		if(y+Tamanho==14) return 1; /*Caso a peca ja esteja no fim da tela, ela nao pode mover*/
		if((*tela).matriz_gui[y+Tamanho+1][x].ocupado==1) return 2; /*Caso exista parte de uma peca embaixo da peca, ela deve parar*/
		((*a).posicao_y)++;
		
		return 0;
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
		((*a).posicao_y)++;
		return 0;
	}
	return 5;
}

