CPP= gcc    #Commande du compilateur
CFLAGS= -std=c99 -Wall -Werror -g #03 Option d'optimisation du programme
LDFLAGS= -lm #Linker
OBJETS2048STRAT = $(SRC2048STRAT:.c=.o)
SRC2048STRAT= ../source/grid.c 2048strategy.c strategy.c
EXECSTRAT= 2048strat

all: ${EXECSTRAT}
	gcc -std=c99 -shared -o libA1_bedin_etcheverry_schiapparelli_efficient.so -fPIC 2048strategy.c
	gcc -std=c99 -shared -o libA1_bedin_etcheverry_schiapparelli_fast.so -fPIC 2048strategy.c

${EXECSTRAT}: $(OBJETS2048STRAT)
	${CPP} $^ ${LDFLAGS} -o $@

grid.o: ../source/grid.c ../header/grid.h

2048strategy.o: 2048strategy.c strategy.h ../header/grid.h

strategy.o: strategy.c strategy.h

clean:	
	rm -fr *.o lib*.so ../source/grid.o

mrproper: clean
	rm -fr ${EXECSTRAT}
