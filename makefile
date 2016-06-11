all: programa

programa: main.o Tela.o Pecas.o Engine.o
	gcc main.o Tela.o Pecas.o Engine.o -o tetris -lncurses

main.o: main.c Tela.c Pecas.c Engine.c
	gcc -c main.c

Tela.o: Tela.c Tela.h Placar.c
	gcc -c Tela.c

Pecas.o: Pecas.c Pecas.h
	gcc -c Pecas.c

Engine.o: Engine.c Engine.h
	gcc -c Engine.c
	
Placar.o: Placar.c Placar.h
	gcc -c Placar.c
