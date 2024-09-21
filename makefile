all: siglaw

siglaw: main.o interfaces.o
	gcc -o siglaw main.o interfaces.o

main.o: main.c src/interfaces.h
	gcc -o main.o main.c -c -W -Wall -pedantic

interfaces.o: src/interfaces.c src/interfaces.h
	gcc -o interfaces.o src/interfaces.c -c -W -Wall -pedantic

clean:
	rm -rf *.o *~ siglaw
