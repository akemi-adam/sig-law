all: siglaw test_interfaces

# Main Program

siglaw: main.o interfaces.o
	gcc -o siglaw main.o interfaces.o

main.o: main.c src/interfaces.h
	gcc -o main.o main.c -c -W -Wall -pedantic

interfaces.o: src/interfaces.c src/interfaces.h
	gcc -o interfaces.o src/interfaces.c -c -W -Wall -pedantic

# Units tests

test_interfaces: tests/TestInterfaces.c interfaces.o
	gcc tests/TestInterfaces.c src/interfaces.c unity/unity.c -o test_interfaces
	./test_interfaces

clean:
	rm -rf *.o *~ siglaw
