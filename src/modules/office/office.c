#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./../../utils/interfaces.h"
#include "./../../utils/validation.h"
#include "./../../utils/storage.h"
#include "./../../utils/str.h"
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
 *  - https://github.com/akemi-adam
 */
void createOffice() {
    Office office;

    Validation enderecoRules[2] = {validateRequired, validateisStringWithNumbers};
    
    printf("---- Cadastrar Escritório ----\n");
    readStrField(office.address, "Endereço", 100, enderecoRules, 2);
    office.isDeleted = false;

    bool status = addElementToFile(&office, sizeof(Office), "offices.dat");

    printf("\n%s\n", status ? "Escritório cadastrado com sucesso!\nPressione <Enter> para prosseguir..." : "Houve um erro ao cadastrar o escritório!");
    proceed();
}

/**
 * Lista todos os escritórios do sistema
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 *  - https://github.com/akemi-adam
 */
void listOffices() {
    int count;
    Office *offices = getOffices(&count);
    
    printf("---- Listar Escritórios ----\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        if (!offices[i].isDeleted) {
            printf("ID: %d\nEndereço: %s\n", i + 1, offices[i].address);
            printf("---------------------------------------------------------\n");
        }
    }
    
    free(offices);
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
 *  - https://github.com/akemi-adam
 */
void readOffice() {
    int intId;
    char id[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive};
    printf("---- Buscar Escritório ----\n");
    readStrField(id, "Código do Escritório", 6, idRules, 3);
    parseInt(id, &intId);
    
    Office *office = findOffice(intId);

    if (office != NULL) {
        printf("----------------------------------------------------------\n");
        printf("ID: %s\nEscritório: %s\n", id, office->address);
        printf("----------------------------------------------------------\n");
        free(office);
    } else {
        printf("O código informado não corresponde a nenhum escritório\n");
    }

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
 *  - https://github.com/akemi-adam
 */
void updateOffice() {
    int intId;
    char id[6];
    Validation idRules[3] = {validateNumber, validatePositive},
        enderecoRules[1] = {validateisStringWithNumbers};

    readStrField(id, "Código do Escritório", 6, idRules, 2);
    parseInt(id, &intId);
    Office *office = findOffice(intId);

    if (office != NULL) {
        printf("Escritório encontrado!\n\n---- Editar Escritório ----\n");
        readStrField(office->address, "Endereço", 100, enderecoRules, 1);
        
        editOffices(intId, office);
        free(office);

        printf("\nEscritório editado com sucesso!\n");
    } else {
        printf("O código informado não corresponde a nenhum escritório\n");
    }

    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Deleta um escritório do sistema
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 *  - https://github.com/akemi-adam
 */
void deleteOffice() {
    int intId;
    char id[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive};
    
    printf("---- Deletar Escritório ----\n");
    readStrField(id, "Código do Escritório", 6, idRules, 3);
    parseInt(id, &intId);
    Office *office = findOffice(intId);

    if (office != NULL) {
        office->isDeleted = true;
        editOffices(intId, office);
        free(office);
        printf("Escritório deletado com sucesso!\n");
    } else {
        printf("O código informado não corresponde a nenhum escritório\n");
    }

    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Exibe o menu do módulo escritórios e pede para o usuário selecionar uma opção
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/zfelip
 *  - https://github.com/akemi-adam
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

/**
 * Retorna uma lista contendo todos os escritórios
 * 
 * @param int *officesNumber: Número de escritórios cadastrados
 * 
 * @return Office*: endereço da lista de escritórios
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
Office* getOffices(int *officesNumber) {
    const size_t structSize = sizeof(Office);
    *officesNumber = getNumberOfElements("offices.dat", structSize);
    Office *offices = (Office*) malloc(structSize * (*officesNumber));
    readFile(offices, structSize, *officesNumber, "offices.dat");

    return offices;
}

/**
 * Retorna um escritório específico a partir de seu ID
 * 
 * @param const char *id: ID a ser procurado
 * 
 * @return Office*|NULL: Escritório correspondente ao ID | NULL, caso não encontre
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
Office* findOffice(int id) {
    int count;
    id--;

    Office* offices = getOffices(&count);
    if (!offices || id < 0 || id >= count) {
        free(offices);
        return NULL;
    }

    if (offices[id].isDeleted) {
        free(offices);
        return NULL;
    }

    Office* office = (Office*) malloc(sizeof(Office));

    *office = offices[id];
    free(offices);

    return office;
}

/**
 * Edita/atualiza a lista de escritórios no arquivo
 * 
 * @param int id: ID do escritório
 * @param Office *office: Escritório
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void editOffices(int id, Office *office) {
    int count;
    Office *offices = getOffices(&count);
    offices[id - 1] = *office;
    saveFile(offices, sizeof(Office), count, "offices.dat");
    free(offices);
}