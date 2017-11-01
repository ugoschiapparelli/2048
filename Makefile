CPP= gcc    #Commande du compilateur
CFLAGS= -std=c99 -Wall -Werror -g
DIR= ./graph ./strategy ./terminal ./test
OBJETSLIB= ./source/grid.o

all:
	for i in ${DIR} ; do \
		${MAKE} -C $$i ; \
	done
	ar -cr libgrid.a ./source/grid.o
	mv libgrid.a ./lib

grid.o: ./source/grid.c ./header/grid.h

lib: ${OBJETSLIB}
	ar -cr libgrid.a $^
	mv libgrid.a ./lib

clean:
	for j in ${DIR} ; do \
		make -C $$j clean ; \
	done
	rm ./lib/libgrid.a

mrproper:
	for k in ${DIR} ; do \
		make -C $$k mrproper ; \
	done
	rm ./lib/libgrid.a

