#include <stdio.h>
#include "Engine.h"
#include "Pecas.h"

void inicia_ncurses(){
	initscr();
	cbreak();
	noecho();
	timeout(0);
}

void finaliza_ncurses(){
	endwin();
}

int fixa_peca(Tela* tela, peca* tetromino){
	int x, y;
	x = tetromino.posicao_x;
	y = tetromino.posicao_y;
  
	for(int i=0; i<*peca.tamanho; i++){
		if(tetromino.orientacao == 0){
			*tela.matriz_gui[x][y+i].ocupado = 1;
    		*tela.matriz_gui[x][y+i].caracter = 'X';  
	}
		if(tetromino.orientacao == 1){
			*tela.matriz_gui[x+i][y].ocupado = 1;
    		*tela.matriz_gui[x+i][y].caracter = 'X';  
  		}
	}
	return 1;
}

int movimento(Tela* tela){
  
	int locked, resultado, retorno;
	peca* tetromino = nova_peca(tela);
	mostra_tela(tela);
	locked = 0;
	while(locked = 0) {
		switch(getch()) {
			case KEY_LEFT:
				retorno = move_peca_x(tela, tetromino, -1);
				break;
			case KEY_RIGHT:
				retorno = move_peca_x(tela, tetromino, 1);
				break;
			case KEY_DOWN:
				resultado = move_peca_y(tela, tetromino);
				break;
			case 'q':  // 'q' de "Quit"
				return 1;
      			break;
		}
	mostra_tela(tela);
	if (resultado < 5){
    	fixa_peca(tela, tetromino);
    	locked = 1;
	}    
	return 0;
}

void jogo() {
	int end = 0;

	Tela* tela = cria_tela();
  
	while(end == 0){
  		mostra_tela(tela);
		end = movimento(tela);
	}
}
