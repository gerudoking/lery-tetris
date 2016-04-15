all: programa

programa: main.o tela.o pecas.o engine.o
	gcc main.o tela.o pecas.o engine.o -o tetris -lncurses

main.o: main.c Tela.c Pecas.c Engine.c
	gcc -c main.c

tela.o: Tela.c Tela.h
	gcc -c Tela.c -o tela

pecas.o: Pecas.c Pecas.h
	gcc -c Pecas.c -o pecas

engine.o: Engine.c Engine.h
	gcc -c Engine.c -o engine
