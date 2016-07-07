#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "Engine.c"


void adicionar_suite(void);
void inicia_ncurses();
int finaliza_ncurses();
void deleta_linha(Tela* tela, int linha);
int movimento(Tela* tela, int* pontuacao);


void teste_inicia_ncurses(){
	
  	inicia_ncurses();
  	CU_ASSERT(COLOR_PAIR(1));
  	CU_ASSERT(COLOR_PAIR(2));
  	CU_ASSERT(COLOR_PAIR(3));
}

void teste_finaliza_ncurses(){
  	CU_ASSERT_TRUE( finaliza_ncurses() == OK );
}


void teste_deleta_linha(){
	int i, j;
	Tela* tela = cria_tela();
	for(i=1; i<25; i++)
		for(j=7; j<15; j++)
			tela->matriz_gui[i][j].ocupado = 1;

	deleta_linha(tela, 10);

	CU_ASSERT_TRUE( (tela->matriz_gui[13][6].ocupado == 0) && (tela->matriz_gui[13][7].ocupado == 1) );
  for(i = 0; i<15; i++){
		for(j = 0; j<25; j++){
        tela->matriz_gui[i][j].caracter = 'X';
        tela->matriz_gui[i][j].ocupado = 1;
      }
  }
  for(i = 0; i<15; i++)
    deleta_linha(tela, i);
  
  CU_ASSERT_TRUE(tela->matriz_gui[8][16].caracter == 32 && tela->matriz_gui[10][21].ocupado == 0);
}

void teste_movimento(){
	int i, j, end=0;
	int pont = 0;
	Tela* tela = cria_tela();

	mostra_tela(tela);
	movimento(tela, &pont);
	
	CU_ASSERT_TRUE(pont == 0);

	for(i = 1; i<24; i++){
		for(j = 12; j<15; j++){
			tela->matriz_gui[j][i].caracter = 'X';
			tela->matriz_gui[j][i].ocupado = 1;
		}
	}
	mostra_tela(tela);
	refresh();
	
	movimento(tela, &pont);
	
	CU_ASSERT_TRUE(pont != 0);
}


void adicionar_suite(){
	CU_pSuite suite;
	suite = CU_add_suite("lery_tetris",NULL,NULL);
	
  	CU_ADD_TEST(suite, teste_inicia_ncurses);
	CU_ADD_TEST(suite, teste_deleta_linha);
	CU_ADD_TEST(suite, teste_movimento);
  	CU_ADD_TEST(suite, teste_finaliza_ncurses);

}

int main(void){

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	adicionar_suite();
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
