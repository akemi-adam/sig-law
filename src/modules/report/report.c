#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./../../utils/interfaces.h"
#include "./../../utils/validation.h"
#include "./../../utils/storage.h"
#include "./../../utils/date.h"
#include "./../../utils/str.h"
#include "./report.h"
#include "../client/client.h"
#include "../lawyer/lawyer.h"
#include "../office/office.h"
#include "../appointment/appointment.h"
#include "../person/person.h"

#ifdef __unix__

#include <termios.h>
#include <unistd.h>


/**
 * Relatórios
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */

void showReportMenu() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
    #endif
    int option = 0, size = 4;
    bool isSelected = false, loop = true;
    char optionsStyles[size][11];
    char options[4][30] = {
        "1. Relatório Advogados", "2. Relatório Clientes", "3. Relatório Escritórios",
        "4. Voltar"
    };
    void (*actions[])() = {
        reportLawyer, reportClient, reportOffice
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

void reportLawyer() {
    printf("Relatório Advogados");
}

void reportClient() {
    printf("Relatório Clientes");
}

void reportOffice() {
    printf("Relatório Escritórios");
}

#endif