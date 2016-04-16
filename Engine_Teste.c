#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h" 
#include "Tela.c"
#include "Pecas.c"
#include "Engine.c"


void adicionar_suite(void);
void fixa_peca(Tela* tela, peca* tetromino);
void deleta_linha(Tela* tela, int linha);

void teste_fixa_peca(void){
	int x, y;
	Tela* tela = cria_tela();
  	peca* tetromino = nova_peca(tela);
  	x = tetromino->posicao_x;
  	y = tetromino->posicao_y;
  	fixa_peca(tela, tetromino);

	CU_ASSERT_TRUE( (tela->matriz_gui[x][y].ocupado == 1) && (tela->matriz_gui[x][y].caracter == 'X') );
}

void teste_deleta_linha(void){
	int i, j;
	Tela* tela = cria_tela();
	for(i=6; i<25; i++)
		for(j=1; j<15; j++)
			tela->matriz_gui[i][j].ocupado = 1;

	deleta_linha(tela, 13);

	CU_ASSERT_TRUE( (tela->matriz_gui[6][13].ocupado == 0) && (tela->matriz_gui[7][13].ocupado == 1) );
}

void adicionar_suite(){
	CU_pSuite suite;
	suite = CU_add_suite("lery_tetris",NULL,NULL);
	
	CU_ADD_TEST(suite, teste_fixa_peca);
	CU_ADD_TEST(suite, teste_deleta_linha);

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
