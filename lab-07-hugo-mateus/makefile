CC=gcc
CFLAGS=-std=c99 -Wall -Werror -lm

all: simulador

simulador: simulador.o pilha.o fila.o peca.o
	$(CC) $(CFLAGS) simulador.o pilha.o fila.o peca.o -o simulador

simulador.o: simulador.c pilha.h fila.h peca.h
	$(CC) $(CFLAGS) -c simulador.c

pilha.o: pilha.c pilha.h
	$(CC) $(CFLAGS) -c pilha.c

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c

peca.o: peca.c peca.h
	$(CC) $(CFLAGS) -c peca.c

clean:
	rm -f *.o simulador
