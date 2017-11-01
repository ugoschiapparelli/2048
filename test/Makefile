CPP= gcc    #Commande du compilateur
CFLAGS= -std=c99 -Wall -Werror -g
LDFLAGS= -lm #Linker
EXECTEST= testGrid
OBJETSTEST = $(SRCTEST:.c=.o)
SRCTEST= ../source/grid.c testGrid.c

all: ${EXECTEST}

${EXECTEST}: $(OBJETSTEST)
	${CPP} $^ ${LDFLAGS} -o $@

grid.o: ../source/grid.c ../header/grid.h

testGrid.o: testGrid.c ../header/grid.h

clean:	
	rm -fr *.o ../source/grid.o

mrproper: clean
	rm -fr ${EXECTEST}
