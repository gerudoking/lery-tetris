gcov :	Placar.c Placar_Teste.c
	gcc -Wall -ftest-coverage -fprofile-arcs -I./CUnit -L./CUnit Placar.c Placar_Teste.c -lcunit -o teste_gcov -lncurses
	./teste_gcov
