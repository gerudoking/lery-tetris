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
  
  x = tetromino->posicao_x;
  y = tetromino->posicao_y;
  
  for(int i=0; i<*peca->tamanho; i++){
    if(tetromino->orientacao == 0){
			tela->matriz_gui[x][y+i]->ocupado = 1;
    	tela->matriz_gui[x][y+i]->caracter = 'X';  
		}
    if(tetromino->orientacao == 1){
			tela->matriz_gui[x+i][y]->ocupado = 1;
    	tela->matriz_gui[x+i][y]->caracter = 'X';  
  	}
  }
  return 1;
}

int deleta_linha(Tela* tela, int linha){
  int i, cont, cont2;
  for (i=1; i<25; i++){
    tela->matriz_gui[i][linha]->ocupado = 0;
    tela->matriz_gui[i][linha]->caracter = ' ';
  }
  for(cont = linha; cont > 0; cont--){
    for(cont2=1; cont2 < 25; cont2++){
      tela->matriz_gui[cont2][cont]->caracter = tela->matriz_gui[cont2-1][cont]->caracter; 
      tela->matriz_gui[cont2][cont]->ocupado = tela->matriz_gui[cont2-1][cont]->ocupado; 
    }  
  }
}

int movimento(Tela* tela, int* pontuacao){
  
	int locked, resultado, retorno, cont, cont2, fechou=0;
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
  }
  
  for(cont = 1; cont < 15; cont++){
    fechou = 0;
    for(cont2=1; cont2 < 25; cont2++){
    	if(tela->matriz_gui[cont2][cont]->caracter == 'X')
      	fechou++;
  	}
    if(fechou == 23){
    	pontuacao += 1; 
    	deleta_linha(tela, cont);
    }
  }
    
  return 0;
}

int jogo() {
	int end = 0;
	int pontuacao = 0;
  
	Tela* tela = cria_tela();
  
	while(end == 0){
  	
  	mostra_tela(tela);
		end = movimento(tela, &pontuacao);
	}
  
  return pontuacao*100;
}
