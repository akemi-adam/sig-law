# Makefile para Projeto C com Testes Unitários usando Unity
# Author: ChatGPT
# Date: 24/11/2024

# Compilador e Flags
CC := gcc
CFLAGS := -W -Wall -pedantic
INCLUDE_DIRS := -I src/utils -I src/modules/appointment -I src/modules/lawyer -I src/modules/client -I src/modules/office -I src/modules/person -I unity

# Diretórios
SRC_DIR := src
TEST_DIR := tests
OBJ_DIR := obj
TEST_OBJ_DIR := $(OBJ_DIR)/tests
UNITY_DIR := unity

# Arquivos Fonte
SRC_FILES := $(filter-out main.c, $(shell find $(SRC_DIR) -type f -name "*.c"))
TEST_SOURCES := $(shell find $(TEST_DIR) -type f -name "*.c")

# Arquivos Objeto
SRC_OBJ_FILES := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, $(TEST_SOURCES))

# Executável Principal
BIN := siglaw

# Executáveis de Teste
TEST_EXECUTABLES := $(patsubst $(TEST_DIR)/%.c, $(TEST_OBJ_DIR)/%, $(TEST_SOURCES))

# Alvo Principal
.PHONY: all siglaw clean test start

# Regra para compilar o executável principal
all: siglaw

siglaw: $(SRC_OBJ_FILES) obj/main.o
	$(CC) $(CFLAGS) $(SRC_OBJ_FILES) obj/main.o -o $(BIN)

obj/main.o: main.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c main.c -o $@

# Regra para compilar arquivos objeto do projeto
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Limpeza de arquivos compilados
clean:
	rm -rf $(OBJ_DIR) $(BIN) *.dat

# Regras para compilar os arquivos de objetos de teste
$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Regras para compilar os executáveis de teste
$(TEST_OBJ_DIR)/%: $(TEST_OBJ_DIR)/%.o $(filter-out obj/main.o, $(SRC_OBJ_FILES)) $(UNITY_DIR)/unity.c $(UNITY_DIR)/unity.h $(UNITY_DIR)/unity_internals.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $< $(filter-out obj/main.o, $(SRC_OBJ_FILES)) $(UNITY_DIR)/unity.c -o $@

# Alvo para compilar e executar todos os testes
test: $(TEST_EXECUTABLES)
	@echo "Executando todos os testes..."
	@for test_exec in $(TEST_EXECUTABLES); do \
		echo "Executando $$test_exec"; \
		./$$test_exec || exit 1; \
	done

# Alvo para iniciar o executável principal
start: siglaw
	./$(BIN)
