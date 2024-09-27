#include "usecases.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./../../utils/interfaces.h"

#ifdef __unix__

#include <termios.h>
#include <unistd.h>

#endif

void showOfficeMenu() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
    #endif
    int aux, option = 0, size = 5;
    bool isSelected = false, loop = true;
    char optionsStyles[size][11];
    setOptionsStyle(optionsStyles, size);
    while (loop) {
        #ifdef __unix__
            system("clear");
            enableRawMode();
        #else
            system("cls");
        #endif
        if (!isSelected) {
            printf("----- Menu Escritório -----\n");
            printf("|                         |\n");
            printf("| %s1. Cadastar escritório%s  |\n", optionsStyles[0], RESET_STYLE);
            printf("| %s2. Mostar escritório%s    |\n", optionsStyles[1], RESET_STYLE);
            printf("| %s3. Editar escritório%s    |\n", optionsStyles[2], RESET_STYLE);
            printf("| %s4. Exluir escritório%s    |\n", optionsStyles[3], RESET_STYLE);
            printf("| %s5. Voltar ao menu%s       |\n", optionsStyles[4], RESET_STYLE);
            printf("|                         |\n");
            printf("---------------------------\n");
            
            aux = option;
            selectOption(&option, size - 1, &isSelected);

            strcpy(optionsStyles[aux], RESET_STYLE);
            strcpy(optionsStyles[option], CYAN_STYLE);
        } else {
            #ifdef __unix__
                disableRawMode(&originalTerminal);
            #endif
            isSelected = false;
            switch (option) {
                case 0:
                    //createOffice();
                    break;
                case 1:
                    //readOffice();
                    break;
                case 2:
                    //updateOffice();
                    break;
                case 3:
                    //deleteOffice();
                    break;
                default:
                    loop = false;
                    break;
            }
        }
    }
}