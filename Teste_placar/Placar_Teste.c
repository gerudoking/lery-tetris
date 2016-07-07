
#include "Placar.c"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

void adicionar_suite(void);

void teste_cria_placar(void);
void teste_atualiza_placar(void);
void teste_mostra_placar(void);

void teste_cria_placar(void){
	int resultado;
	resultado = cria_placar();
	CU_ASSERT_TRUE(!resultado);
}

void teste_atualiza_placar_100(void){
	int resultado;
	resultado = atualiza_placar(100);
	CU_ASSERT_TRUE(!resultado);
}

void teste_atualiza_placar_999999(void){
	int resultado;
	resultado = atualiza_placar(999999);
	CU_ASSERT_TRUE(!resultado);
}


void teste_mostra_placar(void){
	int resultado;
	resultado = mostra_placar();
	CU_ASSERT_TRUE(!resultado);
}

void adicionar_suite(void){
	CU_pSuite suite;

	suite = CU_add_suite("Testes",NULL,NULL);

	CU_ADD_TEST(suite, teste_cria_placar);
	CU_ADD_TEST(suite, teste_mostra_placar);
	CU_ADD_TEST(suite, teste_atualiza_placar100);
	CU_ADD_TEST(suite, teste_atualiza_placar999999);

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
