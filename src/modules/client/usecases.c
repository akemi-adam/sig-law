#include "usecases.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./../../utils/interfaces.h"
#include "./../person/person.h"
#include "client.h"

#ifdef __unix__

#include <termios.h>
#include <unistd.h>

#endif

void createClient() {
    struct Client *client = malloc(sizeof(struct Client));
    client->person = malloc(sizeof(struct Person));
    
    printf("---- Cadastrar Cliente ----\n");
    printf("Nome: ");
    readline(client->person->name, 55);

    printf("CPF: ");
    readline(client->person->cpf, 14);

    printf("E-mail: ");
    readline(client->person->email, 55);

    printf("Telefone: ");
    readline(client->person->telephone, 14);

    free(client->person);
    free(client);

    printf("\nCliente cadastrado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

void listClients() {
    printf("---- Listar Clientes ----\n");
    printf("------------------------------------------------------------------\n");
    printf("ID: %d\nNome: %s\nCPF: %s\nE-mail: %s\nTelefone: %s\n", 1, "", "", "", "");
    printf("------------------------------------------------------------------\n");
    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

void readClient() {

}

void updateClient() {

}

void deleteClient() {

}

void showClientMenu() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
    #endif
    int aux, option = 0, size = 6;
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
            strcpy(optionsStyles[aux], RESET_STYLE);
            selectOption(&option, size - 1, &isSelected);
            strcpy(optionsStyles[option], CYAN_STYLE);
        } else {
            #ifdef __unix__
                disableRawMode(&originalTerminal);
            #endif
            isSelected = false;
            if (option >= 0 && option <= (size - 2)) {
                actions[option](); 
            } 
            else {
                loop = false;
            }
        }
    }
}