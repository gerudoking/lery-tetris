#include "Pecas.c"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
void teste_nova_peca(){
	Tela* b;
	peca* a=nova_peca(b);
	CU_ASSERT_PTR_NOT_NULL(a);
}
void teste_move_peca_x_direita(){
	int resultado;	
	Tela b;
	peca* a=nova_peca(&b);
	resultado=move_peca_x(&b,a,1);
	free(a);
	CU_ASSERT_EQUAL(resultado,5);
}
void teste_move_peca_x_esquerda(){
	int resultado;	
	Tela b;
	peca* a=nova_peca(&b);
	resultado=move_peca_x(&b,a,-1);
	free(a);
	CU_ASSERT_EQUAL(resultado,5);
}
void teste_move_peca_y(){
	int resultado;	
	Tela b;
	peca* a=nova_peca(&b);
	resultado=move_peca_y(&b,a);
	free(a);
	CU_ASSERT_EQUAL(resultado,5);
}
void teste_rotaciona_peca(){
	Tela b;
	peca* a=nova_peca(&b);
	rotaciona_peca(&b,a);
	CU_ASSERT_PTR_NOT_NULL(a);
	free(a);
}
void adicionar_suite(){
	CU_pSuite suite;
	suite=CU_add_suite("Testes de Pecas.c",NULL,NULL);
	CU_ADD_TEST(suite, teste_nova_peca);
	CU_ADD_TEST(suite, teste_move_peca_x_direita);
	CU_ADD_TEST(suite, teste_move_peca_x_esquerda);
	CU_ADD_TEST(suite, teste_move_peca_y);
	CU_ADD_TEST(suite, teste_rotaciona_peca);
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
