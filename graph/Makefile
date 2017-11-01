CPP= gcc    #Commande du compilateur
CFLAGS= -std=c99 -Wall -Werror -g
LDFLAGS= -lm -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer #Linker
OBJETS2048GRAPH = $(SRC2048GRAPH:.c=.o)
SRC2048GRAPH= ../source/grid.c main.c
EXECGRAPH= 2048graph

all: ${EXECGRAPH}

${EXECTEST}: $(OBJETSTEST)
	${CPP} $^ ${LDFLAGS} -o $@

${EXECGRAPH}: $(OBJETS2048GRAPH)
	${CPP} $^ ${LDFLAGS} -o $@

grid.o: ../source/grid.c ../header/grid.h

2048graph.o: main.c ../header/grid.h

clean:	
	rm -fr *.o ../source/grid.o

mrproper: clean
	rm -fr ${EXECGRAPH}
