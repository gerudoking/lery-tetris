#include "Pecas.c"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
/*
*	\author Luiz Felipe Carvalho Duarte
*	\since 30/06/2016
*	\version 1.0
*/
/*	Testamos primeiramente a criação de novas peças por caixa preta.
*	Nos asseguramos de que a função de criação de novas peças não retorna null.
*
*/
void teste_nova_peca(){
	Tela* b;
	peca* a=nova_peca(b);
	CU_ASSERT_PTR_NOT_NULL(a);
	free(a);
}
/*
*	Aqui nos asseguramos de que a função de movimento horizontal funciona, por meio de verificação de seu retorno. São testados os movimentos para a esquerda e direita.
*
*/
void teste_move_peca_x_direita(){
	int resultado;	
	Tela b;
	peca* a=nova_peca(&b);
	resultado=move_peca_x(&b,a,1);
	free(a);
	CU_ASSERT_EQUAL(resultado,0);
}
void teste_move_peca_x_esquerda(){
	int resultado;	
	Tela b;
	peca* a=nova_peca(&b);
	resultado=move_peca_x(&b,a,-1);
	free(a);
	CU_ASSERT_EQUAL(resultado,0);
}
/*
*	Como com o movimento horizontal, nos asseguramos de que a função de movimento vertical retorna
*	o valor que indica o funcionamento correto.
*/
void teste_move_peca_y(){
	int resultado;	
	Tela b;
	peca* a=nova_peca(&b);
	resultado=move_peca_y(&b,a);
	free(a);
	CU_ASSERT_EQUAL(resultado,8);
}
void adicionar_suite(){
	CU_pSuite suite;
	suite=CU_add_suite("Testes de Pecas.c",NULL,NULL);
	CU_ADD_TEST(suite, teste_nova_peca);
	CU_ADD_TEST(suite, teste_move_peca_x_direita);
	CU_ADD_TEST(suite, teste_move_peca_x_esquerda);
	CU_ADD_TEST(suite, teste_move_peca_y);
}
int main(){
if (CUE_SUCCESS != CU_initialize_registry())
    		return CU_get_error();

adicionar_suite();
CU_basic_set_mode(CU_BRM_VERBOSE);
CU_basic_run_tests();
CU_cleanup_registry();
return CU_get_error;
}
