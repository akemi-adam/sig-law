#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./../../utils/interfaces.h"
#include "./../../utils/validation.h"
#include "./../../utils/storage.h"
#include "./../../utils/str.h"
#include "./../../utils/storage.h"
#include "./../person/person.h"
#include "lawyer.h"

#ifdef __unix__

#include <termios.h>
#include <unistd.h>

#endif

/**
 * Formulário para cadastrar um advogado
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void createLawyer() {
    Lawyer lawyer;

    Validation nameRules[2] = {validateRequired, validateString},
        cpfRules[2] = {validateRequired, validateCpf},
        cnaRules[2] = {validateRequired, validateCna},
        emailRules[2] = {validateRequired, validateEmail},
        telephoneRules[2] = {validateRequired, validateTelephone};
    
    printf("---- Cadastrar Advogado ----\n");
    readStrField(lawyer.person.name, "Nome", 55, nameRules, 2);
    readStrField(lawyer.person.cpf, "CPF", 12, cpfRules, 2);
    readStrField(lawyer.cna, "CNA", 13, cnaRules, 2);
    readStrField(lawyer.person.email, "E-mail", 55, emailRules, 2);
    readStrField(lawyer.person.telephone, "Telefone", 14, telephoneRules, 2);

    lawyer.isDeleted = false;

    bool status = addElementToFile(&lawyer, sizeof(Lawyer), "lawyers.dat");

    printf("\n%s\n", status ? "Advogado cadastrado com sucesso!\nPressione <Enter> para prosseguir..." : "Houve um erro ao cadastrar o advogado!");
    proceed();
}

/**
 * Lista todos os advogados do sistema
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void listLawyers() {
    int count;
    Lawyer *lawyers = getLawyers(&count);
    
    printf("---- Listar Advogados ----\n");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        if (!lawyers[i].isDeleted) {
            printf("ID: %d\nNome: %s\nCPF: %s\nCNA: %s\nE-mail: %s\nTelefone: %s\n", i + 1, lawyers[i].person.name, lawyers[i].person.cpf, lawyers[i].cna, lawyers[i].person.email, lawyers[i].person.telephone);
        }
    }
    printf("------------------------------------------------------------------\n");

    free(lawyers);
    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Exibe os dados de um usuário específico
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void readLawyer() {
    int intId;
    char id[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive};
    printf("---- Buscar Advogado ----\n");
    readStrField(id, "Código do Advogado", 6, idRules, 3);

    parseInt(id, &intId);

    Lawyer *lawyer = findLawyer(intId);

    if (lawyer != NULL) {
        printf("------------------------------------------------------------------\n");
        printf("ID: %s\nNome: %s\nCPF: %s\nCNA: %s\nE-mail: %s\nTelefone: %s\n", id, lawyer->person.name, lawyer->person.cpf, lawyer->cna, lawyer->person.email, lawyer->person.telephone);
        printf("------------------------------------------------------------------\n");
        free(lawyer);
    } else {
        printf("O código informado não corresponde a nenhum advogado\n");
    }

    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Formulário para atualizar os dados de um advogado específico
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void updateLawyer() {
    Lawyer lawyer;
    char id[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive},
        nameRules[2] = {validateRequired, validateString},
        cpfRules[2] = {validateRequired, validateCpf},
        cnaRules[2] = {validateRequired, validateCna},
        emailRules[2] = {validateRequired, validateEmail},
        telephoneRules[2] = {validateRequired, validateTelephone};
    
    printf("---- Editar Advogado ----\n");
    readStrField(id, "Código do Advogado", 6, idRules, 3);
    readStrField(lawyer.person.name, "Nome", 55, nameRules, 2);
    readStrField(lawyer.person.cpf, "CPF", 12, cpfRules, 2);
    readStrField(lawyer.cna, "CNA", 13, cnaRules, 2);
    readStrField(lawyer.person.email, "E-mail", 55, emailRules, 2);
    readStrField(lawyer.person.telephone, "Telefone", 14, telephoneRules, 2);

    printf("\nAdvogado editado com sucesso!\nPressione <Enter> para prosseguir...\n");
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
    char id[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive};
    printf("---- Deletar Advogado ----\n");
    readStrField(id, "Código do Advogado", 6, idRules, 3);
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

/**
 * Retorna uma lista contendo todos os advogados
 * 
 * @param int *officesNumber: Número de advogados cadastrados
 * 
 * @return Office*: endereço da lista de advogados
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
Lawyer* getLawyers(int *officesNumber) {
    const size_t structSize = sizeof(Lawyer);
    *officesNumber = getNumberOfElements("lawyers.dat", structSize);
    Lawyer *lawyers = (Lawyer*) malloc(structSize * (*officesNumber));
    readFile(lawyers, structSize, *officesNumber, "lawyers.dat");

    return lawyers;
}

/**
 * Retorna um advogado específico a partir de seu ID
 * 
 * @param const char *id: ID a ser procurado
 * 
 * @return Lawyer*|NULL: Advogado correspondente ao ID | NULL, caso não encontre
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
Lawyer* findLawyer(int id) {
    int count;
    id--;

    Lawyer* lawyers = getLawyers(&count);
    if (!lawyers || id < 0 || id >= count) {
        free(lawyers);
        return NULL;
    }

    if (lawyers[id].isDeleted) {
        free(lawyers);
        return NULL;
    }

    Lawyer* lawyer = (Lawyer*) malloc(sizeof(Lawyer));

    *lawyer = lawyers[id];
    free(lawyers);

    return lawyer;
}


/**
 * Edita/atualiza a lista de advogados no arquivo
 * 
 * @param int id: ID do advogado
 * @param Lawyer *lawyer: Advogado
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void editLawyers(int id, Lawyer *lawyer) {
    int count;
    Lawyer *lawyers = getLawyers(&count);
    lawyers[id - 1] = *lawyer;
    saveFile(lawyers, sizeof(Lawyer), count, "lawyers.dat");
    free(lawyers);
}