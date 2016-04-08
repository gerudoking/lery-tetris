#include <ncurses.h>
#include <stdlib.h>

void inicia_ncurses();

void finaliza_ncurses();

int deleta_linha(Tela* tela, int linha);

int fixa_peca(Tela* tela, peca* tetromino);

int movimento(Tela* tela);

void jogo(); 

