gcov :	Tela.c Tela_Teste.c
	gcc -Wall -ftest-coverage -fprofile-arcs -I./CUnit -L./CUnit Placar.c Tela.c Tela_Teste.c -lcunit -o teste_gcov -lncurses
	./teste_gcov
