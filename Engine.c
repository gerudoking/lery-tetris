#include <stdio.h>
#include <ncurses.h>
#include "Tela.c"
#include "Pecas.c"
#include "Engine.h"
void inicia_ncurses(){
	initscr();
	keypad(stdscr, TRUE);
 	start_color();
  	init_pair(1, COLOR_RED, COLOR_BLACK);//Trataremos o 1 como a cor vermelha nos caracteres
	init_pair(2, COLOR_BLUE, COLOR_BLACK);//E o 2 como azul
	init_pair(3, COLOR_GREEN, COLOR_BLACK);//por sua vez o 3 como verde
}

void finaliza_ncurses(){
	endwin();
}

void fixa_peca(Tela* tela, peca* tetromino){
	int x, y, i;
  
  x = tetromino->posicao_x;
  y = tetromino->posicao_y;
  
  for(i=0; i<tetromino->tamanho; i++){
    if(tetromino->orientacao == 1){
		tela->matriz_gui[y][x+i].ocupado = 1;
    	tela->matriz_gui[y][x+i].caracter = 'X';  
	}
    if(tetromino->orientacao == 0){
		tela->matriz_gui[y+i][x].ocupado = 1;
    	tela->matriz_gui[y+i][x].caracter = 'X';  
  	}
  }
  free(tetromino);
}

void deleta_linha(Tela* tela, int linha){
  int i, cont, cont2;
  for (i=1; i<25; i++){
    tela->matriz_gui[i][linha].ocupado = 0;
    tela->matriz_gui[i][linha].caracter = ' ';
  }
  for(cont = linha; cont > 0; cont--){
    for(cont2=1; cont2 < 25; cont2++){
      tela->matriz_gui[cont2][cont].caracter = tela->matriz_gui[cont2-1][cont].caracter; 
      tela->matriz_gui[cont2][cont].ocupado = tela->matriz_gui[cont2-1][cont].ocupado; 
    }  
  }
}

int movimento(Tela* tela, int* pontuacao){
  
	int locked, resultado, cont, cont2, fechou=0;
	peca* tetromino = nova_peca(tela);

  	mostra_tela(tela);

	locked = 0;
	while(locked == 0) {
		switch(getch()) {
			case KEY_LEFT:
				move_peca_x(tela, tetromino, -1);
				break;
			case KEY_RIGHT:
				move_peca_x(tela, tetromino, 1);
				break;
			case KEY_DOWN:
				resultado = move_peca_y(tela, tetromino);
				break;
			case 'q':  // 'q' de "Quit"
      			return 1;
      			break;
		}
    mostra_tela(tela);
    refresh();
 
    if (resultado < 5){
      fixa_peca(tela, tetromino);
      locked = 1;
    }
  }
  
  for(cont = 1; cont < 15; cont++){
    fechou = 0;
    for(cont2=1; cont2 < 25; cont2++){
    	if(tela->matriz_gui[cont2][cont].caracter == 'X')
      	fechou++;
  	}
    if(fechou == 23){
    	pontuacao += 1; 
    	deleta_linha(tela, cont);
    }
  }
    
  return 0;
}
