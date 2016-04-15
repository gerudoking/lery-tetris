#include "Tela.c"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

void adicionar_suite(void);

void teste_cria_tela(void);
void teste_mostra_tela(void);

void teste_cria_tela(void){
	int resultado;
	Tela* t;
	t = cria_tela();
	if (t == NULL) resultado = 0;
	else resultado = 1;
	CU_ASSERT_TRUE(resultado);
	free(t);
}

void teste_mostra_tela(void){
	int resultado;
	Tela* t;
	t = cria_tela();
	resultado = mostra_tela(t);
	CU_ASSERT_TRUE(!resultado);
	free(t);
}

void teste_mostra_tela_inicial(void){
	int resultado;
	resultado = mostra_tela_inicial();
	CU_ASSERT_TRUE(!resultado);
}

void teste_mostra_tela_final(void){
	int resultado;
	resultado = mostra_tela_final(100);
	CU_ASSERT_TRUE(!resultado);
}

void adicionar_suite(void){
	CU_pSuite suite;

	suite = CU_add_suite("Testes",NULL,NULL);

	CU_ADD_TEST(suite, teste_cria_tela);
	CU_ADD_TEST(suite, teste_mostra_tela);
	CU_ADD_TEST(suite, teste_mostra_tela_inicial);
	CU_ADD_TEST(suite, teste_mostra_tela_final);

}

int main(){
	if (CUE_SUCCESS != CU_initialize_registry())
    		return CU_get_error();
	
	adicionar_suite();
	
	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	
	CU_cleanup_registry();

	return CU_get_error();
}
