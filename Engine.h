#include <ncurses.h>
#include <stdlib.h>

void inicia_ncurses();

void finaliza_ncurses();

int deleta_linha(Tela* tela, int linha);

int movimento(Tela* tela, int* pontuacao);
