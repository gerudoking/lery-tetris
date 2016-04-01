#include "Tela.h"
#include <stdlib.h>

Tela* cria_tela(){
	Tela* t;
	int i, j;

	init_pair(1, COLOR_RED, COLOR_BLACK);

	t = (Tela*) malloc(sizeof(Tela));
	
	for(i = 0; i<25; i++){
		for(j = 0; j<15; j++){
			(*t).matriz_gui[j][i].caracter = 32;
		}
	}

	for(i = 0; i<25; i++){
		(*t).matriz_gui[0][i].caracter = '=';
		(*t).matriz_gui[14][i].caracter = '=';
	}

	for(j = 0; j<15; j++){
		(*t).matriz_gui[j][0].caracter = '|';
		(*t).matriz_gui[j][24].caracter = '|';
	}

	return t;
}

int mostra_tela(Tela* t){
	int i, j;

	attrset(COLOR_PAIR(1));

	for(i = 0; i<15; i++){
		for(j = 0; j<25; j++){
			mvaddch(i, j, (*t).matriz_gui[i][j].caracter);
		}
	}
	return 0;
}
