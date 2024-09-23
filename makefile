.PHONY: test clean

all: test siglaw

# Main Program
siglaw: main.o interfaces.o
	gcc -o siglaw main.o interfaces.o

main.o: main.c src/utils/interfaces.h
	gcc -o main.o main.c -c -W -Wall -pedantic

interfaces.o: src/utils/interfaces.c src/utils/interfaces.h
	gcc -o interfaces.o src/utils/interfaces.c -c -W -Wall -pedantic

# Units tests
test_interfaces: tests/utils/TestInterfaces.c
	gcc tests/utils/TestInterfaces.c src/utils/interfaces.c unity/unity.c -o test_interfaces

# Searches for all files with the pattern test_* and executes those that are executable. If a test fails, the output is 1 and the flow is terminated.
# Author: ChatGPT
test: test_interfaces
	@echo "Running all tests..."
	@for test_exec in test_*; do \
	    if [ -x "$$test_exec" ]; then \
	        echo "Running $$test_exec"; \
	        ./$$test_exec || exit 1; \
	    fi \
	done

clean:
	rm -rf *.o *~ siglaw test_*
