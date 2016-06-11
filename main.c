#include "Pecas.h"
#include "Engine.h"

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
		end = movimento(t, &pontuacao);
	}

	mostra_tela_final(pontuacao*100);
	getch();
	
	mostra_tela_placar(pontuacao*100);
	getch();

	free(t);
	finaliza_ncurses();

	return 0;
}
