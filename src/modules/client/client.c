#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./../../utils/interfaces.h"
#include "./../../utils/validation.h"
#include "./../../utils/str.h"
#include "./../person/person.h"
#include "client.h"

#ifdef __unix__

#include <termios.h>
#include <unistd.h>

#endif

/**
 * Formulário para cadastrar um cliente
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 */
void createClient() {
    Client client;
    
    Validation nameRules[2] = {validateRequired, validateString},
        cpfRules[2] = {validateRequired, validateCpf},
        emailRules[2] = {validateRequired, validateEmail},
        telephoneRules[2] = {validateRequired, validateTelephone};

    printf("---- Cadastrar Cliente ----\n");
    readStrField(client.person.name, "Nome", 55, nameRules, 2);
    readStrField(client.person.cpf, "CPF", 12, cpfRules, 2);
    readStrField(client.person.email, "E-mail", 55, emailRules, 2);
    readStrField(client.person.telephone, "Telefone", 14, telephoneRules, 2);

    printf("\nCliente cadastrado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Lista todos os clientes do sistema
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 */
void listClients() {
    printf("---- Listar Clientes ----\n");
    printf("------------------------------------------------------------------\n");
    printf("ID: %d\nNome: %s\nCPF: %s\nE-mail: %s\nTelefone: %s\n", 1, "", "", "", "");
    printf("------------------------------------------------------------------\n");
    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Exibe os dados de um cliente específico
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 */
void readClient() {
    char id[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive};
    printf("---- Buscar Cliente ----\n");
    readStrField(id, "Código do Cliente", 6, idRules, 3);
    printf("------------------------------------------------------------------\n");
    printf("ID: %s\nNome: %s\nCPF: %s\nE-mail: %s\nTelefone: %s\n", id, "", "", "", "");
    printf("------------------------------------------------------------------\n");
    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Formulário para atualizar os dados de um cliente específico
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 */
void updateClient() {
    Client client;
    char id[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive},
        nameRules[2] = {validateRequired, validateString},
        cpfRules[2] = {validateRequired, validateCpf},
        emailRules[2] = {validateRequired, validateEmail},
        telephoneRules[2] = {validateRequired, validateTelephone};

    printf("---- Editar Cliente ----\n");
    readStrField(id, "Código do Cliente", 6, idRules, 3);
    readStrField(client.person.name, "Nome", 55, nameRules, 2);
    readStrField(client.person.cpf, "CPF", 12, cpfRules, 2);
    readStrField(client.person.email, "E-mail", 55, emailRules, 2);
    readStrField(client.person.telephone, "Telefone", 14, telephoneRules, 2);

    printf("\nCliente editado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Deleta um cliente do sistema
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 */
void deleteClient() {
    char id[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive};
    printf("---- Deletar Cliente ----\n");
    readStrField(id, "Código do Cliente", 6, idRules, 3);
    printf("Cliente deletado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Exibe o menu do módulo cliente e pede para o usuário selecionar uma opção
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 */
void showClientMenu() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
    #endif
    int option = 0, size = 6;
    bool isSelected = false, loop = true;
    char optionsStyles[size][11];
    char options[6][30] = {
        "1. Cadastrar Cliente", "2. Mostrar Clientes", "3. Achar Cliente",
        "4. Editar Cliente", "5. Excluir Cliente", "6. Voltar"
    };
    void (*actions[])() = {
        createClient, listClients, readClient, updateClient, deleteClient
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
            showOptions("Menu Cliente", options, optionsStyles, size);
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
