#include "interfaces.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Desabilita o modo canônico e habilita o raw mode (modo bruto) do terminal
 *
 * Inputs: Void
 * Outputs: Void
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
 * Incrementa ou decrementa um inteiro ao pressionar as teclas de Down-Arrow ou Up-Arrow. Enter é interpretado como a seleção de uma opção.
 * 
 * Inputs:
 *  - int *option: Um ponteiro de inteiro que representa a opção escolhida no menu
 *  - int optionsAmount: Quantidade máxima de opções do menu
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

void showMainMenu() {

    struct termios originalTerminal;
    tcgetattr(STDIN_FILENO, &originalTerminal);
    enableRawMode();

    char optionsStyles[6][30];

    strcpy(optionsStyles[0], CYAN_UNDERLINE_TEXT);
    strcpy(optionsStyles[1], RESET_STYLE);
    strcpy(optionsStyles[2], RESET_STYLE);
    strcpy(optionsStyles[3], RESET_STYLE);
    strcpy(optionsStyles[4], RESET_STYLE);
    strcpy(optionsStyles[5], RESET_STYLE);

    int option = 0, aux;
    while (1) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
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
        selectOption(&option, 5);
        strcpy(optionsStyles[aux], RESET_STYLE);
        strcpy(optionsStyles[option], CYAN_UNDERLINE_TEXT);

    }
    disableRawMode(&originalTerminal);
}

void showClientMenu() {
    //
}

void showLawyerMenu() {
    //
}

void showOfficeMenu() {
    //
}

void showAppointmentMenu() {
    //
}

void print(char message[]) {
    printf("%s\n", message);
}
