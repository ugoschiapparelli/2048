CPP= gcc    #Commande du compilateur
CFLAGS= -std=c99 -Wall -Werror -g 
LDFLAGS= -lm #Linker
EXEC= 2048term
OBJETS2048 = $(SRC2048:.c=.o)
SRC2048= ../source/grid.c 2048terminal.c

all: ${EXEC}

${EXEC}: $(OBJETS2048)
	${CPP} $^ ${LDFLAGS} -o $@

grid.o: ../source/grid.c ../header/grid.h

2048terminal.o: 2048terminal.c ../header/grid.h

clean:	
	rm -fr *.o ../source/grid.o

mrproper: clean
	rm -fr ${EXEC}
