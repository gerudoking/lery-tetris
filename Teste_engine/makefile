gcov :	Pecas.c Engine.c Engine_Teste.c
	gcc -Wall -ftest-coverage -fprofile-arcs -I./CUnit -L./CUnit Placar.c Tela.c Pecas.c Engine_Teste.c -lcunit -lncurses -o Teste_gcov
	./Teste_gcov

CFLAGS = -Wall -ftest-coverage -fprofile-arcs