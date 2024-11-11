# Makefile Author: ChatGPT
# This file is responsible for compiling and creating the executable program
# Furthermore, the make runs the unit tests

CFLAGS := -W -Wall -pedantic
INCLUDE_DIRS := -I src/utils -I src/modules/appointment -I src/modules/lawyer -I src/modules/client -I src/modules/office -I src/modules/person -I src/utils

MODULES := src/modules/appointment/appointment.c src/modules/lawyer/lawyer.c src/modules/client/client.c src/modules/office/office.c
MODULES_OBJS := $(MODULES:.c=.o)

UTILS := src/utils/str.c
UTILS_OBJS := $(UTILS:.c=.o)

.PHONY: test clean

all: test siglaw

siglaw: main.o interfaces.o $(MODULES_OBJS) $(UTILS_OBJS)
	gcc -o siglaw main.o interfaces.o $(MODULES_OBJS) $(UTILS_OBJS)

%.o: %.c
	gcc $(CFLAGS) $(INCLUDE_DIRS) -o $@ $< -c

main.o: main.c src/utils/interfaces.h
	gcc $(CFLAGS) $(INCLUDE_DIRS) -o main.o main.c -c

interfaces.o: src/utils/interfaces.c src/utils/interfaces.h $(MODULES_OBJS)
	gcc $(CFLAGS) $(INCLUDE_DIRS) -o interfaces.o src/utils/interfaces.c -c

str.o: src/utils/str.c src/utils/str.h
	gcc $(CFLAGS) $(INCLUDE_DIRS) -o str.o src/utils/str.c -c

validation.o: src/utils/validation.c src/utils/validation.h
	gcc $(CFLAGS) $(INCLUDE_DIRS) -o validation.o src/utils/validation.c -c

# Unit tests
test_interfaces: tests/utils/TestInterfaces.c $(MODULES_OBJS) $(UTILS_OBJS)
	gcc $(CFLAGS) $(INCLUDE_DIRS) tests/utils/TestInterfaces.c src/utils/interfaces.c src/utils/str.c src/utils/validation.c unity/unity.c $(MODULES) -o test_interfaces

test_str: tests/utils/TestStr.c $(MODULES_OBJS) $(UTILS_OBJS)
	gcc $(CFLAGS) $(INCLUDE_DIRS) tests/utils/TestStr.c src/utils/str.c src/utils/validation.c unity/unity.c -o test_str

test_validation: tests/utils/TestValidation.c $(MODULES_OBJS) $(UTILS_OBJS)
	gcc $(CFLAGS) $(INCLUDE_DIRS) tests/utils/TestValidation.c src/utils/validation.c src/utils/str.c unity/unity.c -o test_validation

# Searches for all files with the pattern test_* and executes those that are executable. If a test fails, the output is 1 and the flow is terminated.
# Author: ChatGPT
test: test_interfaces test_str test_validation
	@echo "Running all tests..."
	@if [ -d . ]; then \
		for test_exec in test_*; do \
			if [ -x "$$test_exec" ]; then \
				echo "Running $$test_exec"; \
				./$$test_exec || exit 1; \
			fi \
		done; \
	fi

# Clean the executable and object files
# Author: ChatGPT
clean:
	find . -type f \( -name "*.o" -o -name "*~" -o -name "siglaw" -o -name "test_*" \) -exec rm -f {} +;
