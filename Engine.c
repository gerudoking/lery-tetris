#include <stdio.h>
#include <ncurses.h>
#include "Pecas.c"
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

int movimento(Tela* tela){
	int locked, resultado, retorno;
	peca* tetromino = nova_peca(tela);
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
		if (resultado == 1) locked = 1;
	}
}

void jogo() {
	int end = 0;

	Tela* tela = cria_tela();
	mostra_tela(tela);
  
	while(end == 0){
		end = movimento(tela);
	}
}
