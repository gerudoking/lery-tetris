all: programa

programa: tela.o pecas.o engine.o
gcc tela.o pecas.o engine.o -o

tela.o: Tela.c Tela.h
gcc -c Tela.c

pecas.o: Pecas.c Pecas.h
gcc -c Pecas.c

engine.o: Engine.c Engine.h
gcc -c Engine.c
