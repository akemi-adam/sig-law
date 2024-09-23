.PHONY: test clean

all: siglaw

# Main Program
siglaw: main.o interfaces.o
	gcc -o siglaw main.o interfaces.o

main.o: main.c src/interfaces.h
	gcc -o main.o main.c -c -W -Wall -pedantic

interfaces.o: src/interfaces.c src/interfaces.h
	gcc -o interfaces.o src/interfaces.c -c -W -Wall -pedantic

# Units tests
test_interfaces: tests/TestInterfaces.c
	gcc tests/TestInterfaces.c src/interfaces.c unity/unity.c -o test_interfaces

# Execute tests
test: test_interfaces
	@echo "Running all tests..."
	./test_interfaces

clean:
	rm -rf *.o *~ siglaw test_interfaces
