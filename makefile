all: 

programa: tela.o pecas.o engine.o
gcc tela.o pecas.o engine.o -o

tela.o: tela.c tela.h
gcc -c tela.c

pecas.o: pecas.c pecas.h
gcc -c pecas.c

engine.o: engine.c engine.h
gcc -c engine.c
