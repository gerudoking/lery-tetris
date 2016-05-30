#include "Tela.h"

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
	WINDOW* janela;

	refresh();
	janela = cria_nova_janela(18,27,0,0);

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


