#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <poll.h>
#include "Pecas.h"

WINDOW* cria_nova_janela(int alt, int larg, int starty, int startx){
	WINDOW* janela_local;

	janela_local = newwin(alt, larg, starty, startx);
	box(janela_local, 0 , 0);
	
	wrefresh(janela_local);

	return janela_local;
}

void destroi_janela(WINDOW* janela_local){//Não sei se será necessária. É usada pra apagar as bordinhas.
	wborder(janela_local, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(janela_local);
	delwin(janela_local);
}

Tela* cria_tela(void){
	Tela* t;
	int i, j;

	t = (Tela*) malloc(sizeof(Tela));
	if(t == NULL) return NULL;
	
	for(i = 0; i<25; i++){
		for(j = 0; j<15; j++){
			(*t).matriz_gui[j][i].caracter = 32;
			(*t).matriz_gui[j][i].ocupado = 0;
			(*t).matriz_gui[j][i].pardecor = 1;
		}
	}

	return t;
}

int mostra_tela(Tela* t){
	int i, j;
	WINDOW* janela = cria_nova_janela(18,27,0,0);
	refresh();

	for(i = 0; i<15; i++){
		for(j = 0; j<25; j++){
			attrset(COLOR_PAIR((*t).matriz_gui[i][j].pardecor));
			mvaddch(i+1, j+1, (*t).matriz_gui[i][j].caracter);
		}
	}
	return 0;
}

int mostra_tela_inicial(void){
	Tela* t = cria_tela();
	mostra_tela(t);

	attrset(COLOR_PAIR(3));
	mvprintw(5, 7, "LERY TETRIS");
	attrset(COLOR_PAIR(2));
	mvprintw(10, 3, "Pressione qualquer");
	mvprintw(11, 3, "tecla para começar");

	free(t);
	return 0;
}

int mostra_tela_final(int pont){
	Tela* t = cria_tela();
	mostra_tela(t);

	attrset(COLOR_PAIR(3));
	mvprintw(5, 8, "GAME OVER");
	attrset(COLOR_PAIR(2));
	mvprintw(10, 4, "Sua pontuação é:");
	mvprintw(11, 12, "%d", pont);

	free(t);
	return 0;
}

peca* nova_peca(Tela* tela){
	int i,j;
	peca* a;
	if((*tela).matriz_gui[1][13].ocupado==1) return NULL;
	a=(peca*)malloc(sizeof(peca));
	(*a).tamanho=((rand() %3)+3);/*Escolhe um tamanho entre 3 e 5 para a peca*/
	(*a).tipo=rand() %6;/*Define o tipo de peca: 0 e vertical, 1 e horizontal, 2 e Z, 3 e quadrado, 4 e L, 5 e T*/
	(*a).cor=rand() %3 + 1;
	(*a).posicao_x=10;
	(*a).posicao_y=4;
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
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if((*a).formato[i][j]!='X') (*a).formato[i][j]=' ';
		}
	}
	return a;
}

int move_peca_x(Tela* tela,peca* a,int direcao){/*vai receber um inteiro, que vai ser ou -1 ou 1, para mostrar se e para mover para a esquerda ou direita, respectivamente*/
	int i,j;
	int x=(*a).posicao_x;
	int y=(*a).posicao_y;
	int cor=(*a).cor;
	x+=direcao;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X' && (*tela).matriz_gui[y+i][x+j].ocupado==1) return 1;
			else if((*a).formato[i][j]=='X') (*tela).matriz_gui[y+i][x+j].caracter=' ';
		}
	}
	(*a).posicao_x+=direcao;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X') {
				(*tela).matriz_gui[y+i][x+j].caracter='X';
				(*tela).matriz_gui[y+i][x+j].pardecor=cor;
			}
		}
	}
	return 0;	
}


int move_peca_y(Tela* tela,peca* a){/*Como so podemos mover para baixo, nao necessitamos de entrada de inteiros*/
	int x=(*a).posicao_x;
	int y=(*a).posicao_y;
	int i,j;
	int cor= (*a).cor;
	
	y++;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X' && (*tela).matriz_gui[y+i][x+j].ocupado==1) return 1;
			else if((*a).formato[i][j]=='X') (*tela).matriz_gui[y+i][x+j].caracter=' ';
		}
	}

	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((*a).formato[i][j]=='X') {
				(*tela).matriz_gui[y+i][x+j].caracter='X';
				(*tela).matriz_gui[y+i][x+j].pardecor=cor;
			}
		}
	}
	return 0;
}
peca* rotaciona_peca(peca* a,Tela* tela){
	int i,j;
	char compara[7][7];
	int x=(*a).posicao_x;
	int y=(*a).posicao_y;
	
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			compara[j][i]=(*a).formato[i][j];
		}	
	}
	
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if(compara[i][j]=='X' && (*tela).matriz_gui[y+i][x+j].ocupado==1) return 1;
		}
	}
	
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			(*a).formato[i][j]=compara[i][j];
		}
	}
	return 0;
}

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

int main(){

	srand(time(NULL));

	int end = 0;
	int pontuacao = 0;
	
	inicia_ncurses();

	Tela* t = cria_tela();

	mostra_tela_inicial();
	getch();
  
	while(end == 0){
  	
  		mostra_tela(t);
  		//getch();
		end = movimento(t, &pontuacao);
	}

	mostra_tela_final(pontuacao*100);
	getch();

	free(t);
	finaliza_ncurses();

	return 0;
}
