#include "usecases.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./../../utils/interfaces.h"
#include "./../person/person.h"
#include "lawyer.h"

#ifdef __unix__

#include <termios.h>
#include <unistd.h>

#endif

void createLawyer() {
    struct Lawyer *lawyer = malloc(sizeof(struct Lawyer));
    lawyer->person = malloc(sizeof(struct Person));
    
    printf("---- Cadastrar Advogado ----\n");
    printf("Nome: ");
    readline(lawyer->person->name, 55);

    printf("CPF: ");
    readline(lawyer->person->cpf, 14);

    printf("CNA: ");
    readline(lawyer->cna, 15);

    printf("E-mail: ");
    readline(lawyer->person->email, 55);

    printf("Telefone: ");
    readline(lawyer->person->telephone, 14);

    free(lawyer->person);
    free(lawyer);

    printf("\nUsuário cadastrado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

void listLawyers() {
    printf("---- Listar Advogados ----\n");
    printf("------------------------------------------------------------------\n");
    printf("ID: %d\nNome: %s\nCPF: %s\nCNA: %s\nE-mail: %s\nTelefone: %s\n", 1, "", "", "", "", "");
    printf("------------------------------------------------------------------\n");
    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

void readLawyer() {
    int id;
    printf("---- Buscar Advogado ----\nCódigo do Advogado: ");
    scanf("%d", &id);
    printf("------------------------------------------------------------------\n");
    printf("ID: %d\nNome: %s\nCPF: %s\nCNA: %s\nE-mail: %s\nTelefone: %s\n", id, "", "", "", "", "");
    printf("------------------------------------------------------------------\n");
    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

void updateLawyer() {
    struct Lawyer *lawyer = malloc(sizeof(struct Lawyer));
    lawyer->person = malloc(sizeof(struct Person));
    int id;
    
    printf("---- Editar Advogado ----\nCódigo do Advogado: ");
    scanf("%d", &id);
    flushInput();

    printf("Nome: ");
    readline(lawyer->person->name, 55);

    printf("CPF: ");
    readline(lawyer->person->cpf, 14);

    printf("CNA: ");
    readline(lawyer->cna, 15);

    printf("E-mail: ");
    readline(lawyer->person->email, 55);

    printf("Telefone: ");
    readline(lawyer->person->telephone, 14);

    free(lawyer->person);
    free(lawyer);

    printf("\nUsuário editado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Deleta um advogado do sistema
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void deleteLawyer() {
    int id;
    printf("---- Deletar Advogado ----\nCódigo do Advogado: ");
    scanf("%d", &id);
    printf("Advogado deletado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Exibe o menu do módulo advogado e que pede para o usuário selecionar uma opção
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void showLawyerMenu() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
    #endif
    int option = 0, size = 6;
    bool isSelected = false, loop = true;
    char optionsStyles[size][11];
    char options[6][30] = {
        "1. Cadastrar Advogado", "2. Mostrar Advogados", "3. Achar advogado",
        "4. Editar Advogado", "5. Excluir Advogado", "6. Voltar"
    };
    void (*actions[])() = {
        createLawyer, listLawyers, readLawyer, updateLawyer, deleteLawyer
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
            showOptions("Menu Advogado", options, optionsStyles, size);
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