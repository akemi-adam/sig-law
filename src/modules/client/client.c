#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./../../utils/interfaces.h"
#include "./../../utils/validation.h"
#include "./../../utils/storage.h"
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
    client.isDeleted = false;

    bool status = addElementToFile(&client, sizeof(Client), "clients.dat");

    printf("\n%s\n", status ? "Cliente cadastrado com sucesso!\nPressione <Enter> para prosseguir..." : "Houve um erro ao cadastrar o cliente!");
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
    int count;
    Client *clients = getClients(&count);

    printf("---- Listar Clientes ----\n");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        if (!clients[i].isDeleted) {
            printf("ID: %d\nNome: %s\nCPF: %s\nE-mail: %s\nTelefone: %s\n", i + 1, clients[i].person.name, clients[i].person.cpf, clients[i].person.email, clients[i].person.telephone);
            printf("------------------------------------------------------------------\n");
        }
    }

    free(clients);
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
    int intId;
    char id[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive};
    printf("---- Buscar Cliente ----\n");
    readStrField(id, "Código do Cliente", 6, idRules, 3);
    parseInt(id, &intId);
    Client *client = findClient(intId);

    if (client != NULL) {
        printf("------------------------------------------------------------------\n");
        printf("ID: %s\nNome: %s\nCPF: %s\nE-mail: %s\nTelefone: %s\n", id, client->person.name, client->person.cpf, client->person.email, client->person.telephone);
        printf("------------------------------------------------------------------\n");
        free(client);
    } else {
        printf("O código informado não corresponde a nenhum cliente\n");
    }

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
    int intId;
    char id[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive},
        nameRules[1] = {validateString},
        cpfRules[1] = {validateCpf},
        emailRules[1] = {validateEmail},
        telephoneRules[1] = {validateTelephone};

    readStrField(id, "Código do Cliente", 6, idRules, 3);
    parseInt(id, &intId);
    Client *client = findClient(intId);

    if (client != NULL) {
        printf("Cliente encontrado!\n\n---- Editar Cliente ----\n");
        readStrField(client->person.name, "Nome", 55, nameRules, 1);
        readStrField(client->person.cpf, "CPF", 12, cpfRules, 1);
        readStrField(client->person.email, "E-mail", 55, emailRules, 1);
        readStrField(client->person.telephone, "Telefone", 14, telephoneRules, 1);

        editClients(intId, client);
        free(client);

        printf("\nCliente editado com sucesso!\n");
    } else {
        printf("O código informado não corresponde a nenhum cliente\n");
    }

    printf("\nPressione <Enter> para prosseguir...\n");
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

/**
 * Retorna uma lista contendo todos os clientes
 * 
 * @param int *officesNumber: Número de clientes cadastrados
 * 
 * @return Office*: endereço da lista de clientes
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
Client* getClients(int *officesNumber) {
    const size_t structSize = sizeof(Client);
    *officesNumber = getNumberOfElements("clients.dat", structSize);
    Client *clients = (Client*) malloc(structSize * (*officesNumber));
    readFile(clients, structSize, *officesNumber, "clients.dat");

    return clients;
}

/**
 * Retorna um cliente específico a partir de seu ID
 * 
 * @param const char *id: ID a ser procurado
 * 
 * @return Client*|NULL: Cliente correspondente ao ID | NULL, caso não encontre
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
Client* findClient(int id) {
    int count;
    id--;

    Client* clients = getClients(&count);
    if (!clients || id < 0 || id >= count) {
        free(clients);
        return NULL;
    }

    if (clients[id].isDeleted) {
        free(clients);
        return NULL;
    }

    Client* client = (Client*) malloc(sizeof(Client));

    *client = clients[id];
    free(clients);

    return client;
}


/**
 * Edita/atualiza a lista de clientes no arquivo
 * 
 * @param int id: ID do cliente
 * @param Client *client: Cliente
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void editClients(int id, Client *client) {
    int count;
    Client *clients = getClients(&count);
    clients[id - 1] = *client;
    saveFile(clients, sizeof(Client), count, "clients.dat");
    free(clients);
}