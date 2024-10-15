# Makefile Author: ChatGPT
# This file is responsible for compiler and create the executable program
# Furthermore, the make run the units tests

CFLAGS := -W -Wall -pedantic
INCLUDE_DIRS := -I src/utils -I src/modules/appointment -I src/modules/lawyer -I src/modules/client -I src/modules/office -I src/modules/person -I src/utils

MODULES := src/modules/appointment/usecases.c src/modules/lawyer/usecases.c src/modules/client/usecases.c src/modules/office/usecases.c
MODULES_OBJS := $(MODULES:.c=.o)

.PHONY: test clean

all: test siglaw

siglaw: main.o interfaces.o $(MODULES_OBJS)
	gcc -o siglaw main.o interfaces.o $(MODULES_OBJS)

%.o: %.c
	gcc $(CFLAGS) $(INCLUDE_DIRS) -o $@ $< -c

main.o: main.c src/utils/interfaces.h
	gcc $(CFLAGS) $(INCLUDE_DIRS) -o main.o main.c -c

interfaces.o: src/utils/interfaces.c src/utils/interfaces.h $(MODULES_OBJS)
	gcc $(CFLAGS) $(INCLUDE_DIRS) -o interfaces.o src/utils/interfaces.c -c

# Units tests
test_interfaces: tests/utils/TestInterfaces.c $(MODULES_OBJS)
	gcc $(CFLAGS) $(INCLUDE_DIRS) tests/utils/TestInterfaces.c src/utils/interfaces.c unity/unity.c $(MODULES) -o test_interfaces

# Searches for all files with the pattern test_* and executes those that are executable. If a test fails, the output is 1 and the flow is terminated.
# Author: ChatGPT
test: test_interfaces
	@echo "Running all tests..."
	@if [ -d . ]; then \
		for test_exec in test_*; do \
			if [ -x "$$test_exec" ]; then \
				echo "Running $$test_exec"; \
				./$$test_exec || exit 1; \
			fi \
		done; \
	fi

# Clean the executable and objects files
# Author: ChatGPT
clean:
	find . -type f \( -name "*.o" -o -name "*~" -o -name "siglaw" -o -name "test_*" \) -exec rm -f {} +; \
