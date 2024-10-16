#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./../../utils/interfaces.h"
#include "office.h"

#ifdef __unix__

#include <termios.h>
#include <unistd.h>

#endif

/**
 * Formulário para cadastrar um escritório
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 */
void createOffice() {
    Office *office = (Office*) malloc(sizeof(Office));
    
    printf("---- Cadastrar Escritório ----\n");
    printf("Endereço: ");
    readline(office->address, 100);

    free(office);

    printf("\nEscritório cadastrado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Lista todos os escritórios do sistema
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 */
void listOffices() {
    printf("---- Listar Escritórios ----\n");
    printf("---------------------------------------------------------\n");
    printf("ID: %d\nEndereço: %s\n", 1, "");
    printf("---------------------------------------------------------\n");
    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Exibe os dados de um escritório específico
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 */
void readOffice() {
    int id;
    printf("---- Buscar Escritório ----\nCódigo do Escritório: ");
    scanf("%d", &id);
    printf("----------------------------------------------------------\n");
    printf("ID: %d\nEscritório: %s\n", id, "");
    printf("----------------------------------------------------------\n");
    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Formulário para atualizar os dados de um escritório específico
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 */
void updateOffice() {
    Office *office = (Office*) malloc(sizeof(Office));
    int id;
    
    printf("---- Editar Escritório ----\nCódigo do Escritório: ");
    scanf("%d", &id);
    flushInput();

    printf("Endereço: ");
    readline(office->address, 100);

    free(office);

    printf("\nEscritório editado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Deleta um escritório do sistema
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 */
void deleteOffice() {
    int id;
    printf("---- Deletar Escritório ----\nCódigo do Escritório: ");
    scanf("%d", &id);
    printf("Escritório deletado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Exibe o menu do módulo escritórios e pede para o usuário selecionar uma opção
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 */
void showOfficeMenu() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
    #endif
    int option = 0, size = 6;
    bool isSelected = false, loop = true;
    char optionsStyles[size][11];
    char options[6][30] = {
        "1. Cadastrar Escritório", "2. Mostrar Escritórios", "3. Achar Escritório",
        "4. Editar Escritório", "5. Excluir Escritório", "6. Voltar"
    };
    void (*actions[])() = {
        createOffice, listOffices, readOffice, updateOffice, deleteOffice
    };
    setOptionsStyle(optionsStyles, size);
    while (loop) {
        #ifdef __unix__
            system("clear");
            enableRawMode();
        #else
            system("cls");
        #endif
        if (!isSelected) {
            showOptions("Menu Escritório", options, optionsStyles, size);
            strcpy(optionsStyles[option], RESET_STYLE);
            selectOption(&option, size - 1, &isSelected);
            strcpy(optionsStyles[option], CYAN_STYLE);
        } else {
            #ifdef __unix__
                disableRawMode(&originalTerminal);
            #endif
            isSelected = false;
            if (option >= 0 && option <= (size - 2)) {
                actions[option]();
            } else {
                loop = false;
            }
        }
    }
}
