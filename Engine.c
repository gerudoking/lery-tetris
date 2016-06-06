#include <stdio.h>
#include <ncurses.h>
#include "Pecas.h"
#include <unistd.h>
#include <poll.h>

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
  int i, vert, hori;
  for (i=0; i<25; i++){
    tela->matriz_gui[linha][i].ocupado = 0;
    tela->matriz_gui[linha][i].caracter = 32;
  }
  for(vert = linha; vert > 0; vert--){
    for(hori=0; hori < 25; hori++){
      tela->matriz_gui[vert][hori].caracter = tela->matriz_gui[vert-1][hori].caracter; 
      tela->matriz_gui[vert][hori].ocupado = tela->matriz_gui[vert-1][hori].ocupado; 
    }  
  }
}

int movimento(Tela* tela, int* pontuacao){
  
	int locked, resultado, cont, cont2, fechou = 0, gravidade = 1; // gravidade é o número de células que a peça cai a cada segundo.
	peca* tetromino = nova_peca(tela);
	struct pollfd poll1 = { STDIN_FILENO, POLLIN|POLLPRI };

	if(tetromino == NULL)
		return 1;

  	mostra_tela(tela);

	locked = 0;
	while(locked == 0) {
		if(poll(&poll1, 1, (1000/gravidade))) {
			switch(getch()) {
				case KEY_LEFT:
					move_peca_x(tela, tetromino, -1);
					break;
				case KEY_RIGHT:
					move_peca_x(tela, tetromino, 1);
					break;
				case KEY_DOWN:
					gravidade = gravidade*2;
					break;
				case 'q':  // 'q' de "Quit"
	      			return 1;
	      			break;
	      		default:
	      			break;
			}
		}
		else {
			resultado = move_peca_y(tela, tetromino);
			if (resultado < 5){
				fixa_peca(tela, tetromino);
				locked = 1;
				break;
				
			}
		}
		mostra_tela(tela);
		refresh();	
	}
  
  	for(cont = 0; cont < 15; cont++){
	    fechou = 0;
	    for(cont2=0; cont2 < 25; cont2++){
	    	if(tela->matriz_gui[cont][cont2].caracter == 'X')
	      	fechou++;
  		}
    	if(fechou == 23){
    		*pontuacao += 1; 
    		deleta_linha(tela, cont);
    	}
  	}
    
  return 0;
}
