
gcov :	Pecas.c Pecas_Teste.c
	gcc -Wall -ftest-coverage -fprofile-arcs -I./CUnit -L./CUnit Placar.c Tela.c Pecas_Teste.c -lcunit -lncurses -o teste_pecas_gcov
	./teste_pecas_gcov
CFLAGS = -Wall -ftest-coverage -fprofile-arcs
