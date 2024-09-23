#include "interfaces.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __unix__

#include <termios.h>
#include <unistd.h>

/*
 * Desabilita o modo canônico e habilita o raw mode (modo bruto) do terminal
 *
 * Inputs: Void
 * Outputs: Void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 *  - https://www.quora.com/How-can-I-take-arrow-keys-as-input-in-C
 * 
 * References:
 *  - https://man7.org/linux/man-pages/man3/termios.3.html
 *  - https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
 *  - https://www.quora.com/How-can-I-take-arrow-keys-as-input-in-C
 */
void enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/*
 * Desabilita o raw mode e volta o terminal para a configuração original
 *
 * Inputs:
 *  - struct termios *originalTerminal: Configuração do terminal original
 * Outputs: Void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 *  - https://www.quora.com/How-can-I-take-arrow-keys-as-input-in-C
 * 
 * References:
 *  - https://man7.org/linux/man-pages/man3/termios.3.html
 *  - https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
 *  - https://www.quora.com/How-can-I-take-arrow-keys-as-input-in-C
 */
void disableRawMode(struct termios *originalTerminal) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, originalTerminal);
}

/*
 * Incrementa ou decrementa um inteiro ao pressionar as teclas de Down-Arrow (B) ou Up-Arrow (A). Enter é interpretado como a seleção de uma opção.
 * Obs.: Funciona apenas em UNIX
 * 
 * Inputs:
 *  - int *option: Um ponteiro de inteiro que representa a opção escolhida no menu
 *  - int optionsAmount: Quantidade máxima de opções do menu
 *  - bool *isSelected: Ponteiro para uma variável booleana que define se o usuário escolheu sua opção
 *
 * Outputs: Void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 *  - https://www.quora.com/How-can-I-take-arrow-keys-as-input-in-C
 * 
 * References:
 *  - https://man7.org/linux/man-pages/man3/termios.3.html
 *  - https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
 *  - https://www.quora.com/How-can-I-take-arrow-keys-as-input-in-C
 */
void selectOption(int *option, int optionsAmount, bool *isSelected) {
    char buf[3];
    if (read(STDIN_FILENO, buf, 1) == 1) {
        if (buf[0] == '\n') {
            *isSelected = true;
        } else if (read(STDIN_FILENO, buf + 1, 1) == 1 && read(STDIN_FILENO, buf + 2, 1) == 1) {
            switch (buf[2]) {
                case 'A':
                    *option = (*option > 0) ? *option - 1 : optionsAmount;
                    break;
                case 'B':
                    *option = (*option < optionsAmount) ? *option + 1 : 0;
                    break;
            }
        }
    }
}

#else

#include <conio.h>

/**
 * Incrementa ou decrementa um inteiro ao pressionar as teclas de Down-Arrow (72) ou Up-Arrow (80). Enter é interpretado como a seleção de uma opção.
 * 
 * Obs.: Funciona apenas em Windows
 * 
 * Inputs:
 *  - int *option: Um ponteiro de inteiro que representa a opção escolhida no menu
 *  - int optionsAmount: Quantidade máxima de opções do menu
 *  - bool *isSelected: Ponteiro para uma variável booleana que define se o usuário escolheu sua opção
 *
 * Outputs: Void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 *  - https://www.quora.com/How-can-I-take-arrow-keys-as-input-in-C
 * 
 * References:
 *  - https://www.quora.com/How-can-I-take-arrow-keys-as-input-in-C
 */
void selectOption(int *option, int optionsAmount, bool *isSelected) {
    int ch = getch();
    if (ch == 13) {
        *isSelected = true;
    } else if (ch == 0 || ch == 224) {
        ch = getch();
        switch (ch) {
            case 72:
                *option = (*option > 0) ? *option - 1 : optionsAmount;
                break;
            case 80:
                *option = (*option < optionsAmount) ? *option + 1 : 0;
                break;
        }
    }
}

#endif

void setOptionsStyle(char optionsStyles[][11], int size) {
    strcpy(optionsStyles[0], CYAN_UNDERLINE_TEXT);
    for (int i = 1; i < size; i++) {
        strcpy(optionsStyles[i], RESET_STYLE);
    }
}

/**
 * Exibe o menu principal
 * 
 * Inputs: Void
 * Outputs: Void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 * 
 * References:
 *  - https://man7.org/linux/man-pages/man3/termios.3.html
 *  - https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
 *  - https://www.quora.com/How-can-I-take-arrow-keys-as-input-in-C
 */
void showMainMenu() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
        enableRawMode();
    #endif
    int size = 6;
    char optionsStyles[size][11];
    setOptionsStyle(optionsStyles, size);

    int option = 0, aux;
    bool isSelected = false;
    while (true) {
        #ifdef __unix__
            system("clear");
        #else
            system("cls");
        #endif
        if (!isSelected) {
            printf("----- Menu Principal -----\n");
            printf("|                        |\n");
            printf("| %s1. Módulo clientes%s     |\n", optionsStyles[0], RESET_STYLE);
            printf("| %s2. Módulo Advogados%s    |\n", optionsStyles[1], RESET_STYLE);
            printf("| %s3. Módulo Escritórios%s  |\n", optionsStyles[2], RESET_STYLE);
            printf("| %s4. Módulo Agendamentos%s |\n", optionsStyles[3], RESET_STYLE);
            printf("| %s5. Módulo Sobre%s        |\n", optionsStyles[4], RESET_STYLE);
            printf("| %s6. Módulo Equipe%s       |\n", optionsStyles[5], RESET_STYLE);
            printf("|                        |\n");
            printf("--------------------------\n");
            
            aux = option;
            selectOption(&option, size - 1, &isSelected);

            strcpy(optionsStyles[aux], RESET_STYLE);
            strcpy(optionsStyles[option], CYAN_UNDERLINE_TEXT);
        } else {
            #ifdef __unix__
                disableRawMode(&originalTerminal);
            #endif
            isSelected = false;
            switch (option) {
                case 0:
                    showClientMenu();
                    break;
                case 1:
                    showLawyerMenu();
                    break;
                case 2:
                    showOfficeMenu();
                    break;
                case 3:
                    showAppointmentMenu();
                    break;
                case 4:
                    // Módulo Sobre
                    break;
                case 5:
                    // Módulo Equipe
                    break;
                default:
                    // Volta no menu
                    break;
            }
            #ifdef __unix__
                enableRawMode();
            #endif
        }

    }
}

void showClientMenu() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
        enableRawMode();
    #endif
    int size = 5;
    char optionsStyles[size][11];
    setOptionsStyle(optionsStyles, size);

    int option = 0, aux;
    bool isSelected = false;
    bool loop = true;
    while (loop) {
        #ifdef __unix__
            system("clear");
        #else
            system("cls");
        #endif
        if (!isSelected) {
            printf("----- Menu Cliente -----\n");
            printf("|                      |\n");
            printf("| %s1. Cadastar cliente%s  |\n", optionsStyles[0], RESET_STYLE);
            printf("| %s2. Mostar cliente%s    |\n", optionsStyles[1], RESET_STYLE);
            printf("| %s3. Editar cliente%s    |\n", optionsStyles[2], RESET_STYLE);
            printf("| %s4. Exluir cliente%s    |\n", optionsStyles[3], RESET_STYLE);
            printf("| %s5. Voltar ao menu%s    |\n", optionsStyles[4], RESET_STYLE);
            printf("|                      |\n");
            printf("------------------------\n");
            
            aux = option;
            selectOption(&option, size - 1, &isSelected);

            strcpy(optionsStyles[aux], RESET_STYLE);
            strcpy(optionsStyles[option], CYAN_UNDERLINE_TEXT);
        } else {
            #ifdef __unix__
                disableRawMode(&originalTerminal);
            #endif
            isSelected = false;
            switch (option) {
                case 0:
                    //createClient();
                    break;
                case 1:
                    //readClient();
                    break;
                case 2:
                    //updateClient();
                    break;
                case 3:
                    //deleteClient();
                    break;
                default:
                    loop = false;
                    break;
            }
            #ifdef __unix__
                enableRawMode();
            #endif
        }
    }
}

void showLawyerMenu() {
    #ifdef _unix_
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
        enableRawMode();
    #endif
    int size = 5;
    char optionsStyles[size][11];
    setOptionsStyle(optionsStyles, size);

    int option = 0, aux;
    bool isSelected = false;
    bool loop = true;
    while (loop) {
        #ifdef _unix_
            system("clear");
        #else
            system("cls");
        #endif
        if (!isSelected) {
            printf("----- Menu Advogado -----\n");
            printf("|                       |\n");
            printf("| %s1. Cadastar advogado%s  |\n", optionsStyles[0], RESET_STYLE);
            printf("| %s2. Mostar advogado%s    |\n", optionsStyles[1], RESET_STYLE);
            printf("| %s3. Editar advogado%s    |\n", optionsStyles[2], RESET_STYLE);
            printf("| %s4. Exluir advogado%s    |\n", optionsStyles[3], RESET_STYLE);
            printf("| %s5. Voltar ao menu%s     |\n", optionsStyles[4], RESET_STYLE);
            printf("|                       |\n");
            printf("-------------------------\n");
            
            aux = option;
            selectOption(&option, size - 1, &isSelected);

            strcpy(optionsStyles[aux], RESET_STYLE);
            strcpy(optionsStyles[option], CYAN_UNDERLINE_TEXT);
        } else {
            #ifdef _unix_
                disableRawMode(&originalTerminal);
            #endif
            isSelected = false;
            switch (option) {
                case 0:
                    //createLawyer();
                    break;
                case 1:
                    //readLawyer();
                    break;
                case 2:
                    //updateLawyer();
                    break;
                case 3:
                    //deleteLawyer();
                    break;
                default:
                    loop = false;
                    break;
            }
            #ifdef _unix_
                enableRawMode();
            #endif
        }
    }
}

void showOfficeMenu() {
    #ifdef _unix_
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
        enableRawMode();
    #endif
    int size = 5;
    char optionsStyles[size][11];
    setOptionsStyle(optionsStyles, size);

    int option = 0, aux;
    bool isSelected = false;
    bool loop = true;
    while (loop) {
        #ifdef _unix_
            system("clear");
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
            strcpy(optionsStyles[option], CYAN_UNDERLINE_TEXT);
        } else {
            #ifdef _unix_
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
            #ifdef _unix_
                enableRawMode();
            #endif
        }
    }
}

void showAppointmentMenu() {
    //
}

void print(char message[]) {
    printf("%s\n", message);
}
