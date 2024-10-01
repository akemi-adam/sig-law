#include "interfaces.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../modules/appointment/usecases.h"
#include "./../lawyer/usecases.h"
#include "./../office/usecases.h"
#include "./../client/usecases.h"

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

/**
 * Função que espera o usuário pressionar qualquer tecla
 * 
 * Inputs: Void
 * 
 * Outputs: Void
 */
bool proceed() {
    char buf[3];
    return read(STDIN_FILENO, buf, 1) == 1;
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

/**
 * Função que espera o usuário pressionar qualquer tecla
 * 
 * Obs.: Funciona apenas em Windows
 * 
 * Inputs: Void
 * 
 * Outputs: Void
 */
bool proceed() {
    return (bool) getch();
}

#endif

/**
 * Limpa o buffer de entrada
 * 
 * Inptus: Void
 * Outputs: Void
 * 
 * Authors:
 *  - Huw Collingbourne
 * 
 * References:
 *  - https://www.youtube.com/watch?v=zWIgtikk6ig&t=512s
 */
void flushInput() {
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * Ler os dados de entrada do teclado em uma string de tamanho x
 * 
 * Inputs:
 *  - char str[]: String a ser armazenada os dados do teclado
 *  - int maxLength: Tamanho máximo da string
 * 
 * Outputs: Void
 * 
 * Authors:
 *  - Huw Collingbourne
 * 
 * References:
 *  - https://www.youtube.com/watch?v=zWIgtikk6ig&t=512s
 */
void readline(char str[], int maxLength) {
    char ch;
    int i = 0;
    while (true) {
        ch = getchar();
        if (ch == '\n' || ch == EOF) {
            break;
        } else if (i < maxLength - 1) {
            str[i] = ch;
            i++;
        }
    }
    str[i] = '\0';
}

/**
 * Define os valores de estilo padrões de um array de opções
 * 
 * @param char optionsStyles[][11]: Array do estilo das opções
 * @param int size: Tamanho máximo do array
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void setOptionsStyle(char optionsStyles[][11], int size) {
    strcpy(optionsStyles[0], CYAN_STYLE);
    for (int i = 1; i < size; i++) {
        strcpy(optionsStyles[i], RESET_STYLE);
    }
}

/**
 * Exibe um menu de opções
 * 
 * @param char titles[]: Título do menu de opções
 * @param char options[][30]: Array de opções
 * @param char optionsStyles[][11]: Array de opções
 * @param int size: Tamanho máximo do array
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void showOptions(char title[], char options[][30], char optionsStyles[][11], int size) {
    printf("----- %s -----\n", title);
    printf("|                        |\n");
    for (int i = 0; i < size; i++) {
        printf("| %s%-*s%s|\n", optionsStyles[i], 23, options[i], RESET_STYLE);
    }
    printf("|                        |\n");
    printf("--------------------------\n");
    
}

void showGenericInfo(char message[]) {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
        enableRawMode();
    #endif
    printf("%s", message);
    proceed();
    #ifdef __unix__
        disableRawMode(&originalTerminal);
    #endif 
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
    #endif
    int option = 0, size = 7;
    char options[7][30] = {
        "1. Modulo Clientes", "2. Modulo Advogados", "3. Modulo Escritorios",
        "4. Modulo Agendamentos", "5. Modulo Sobre", "6. Modulo Equipe", "7. Encerrar Programa"
    };
    char optionsStyles[size][11];
    bool isSelected = false, loop = true;
    void (*actions[])() = {
        showClientMenu, showLawyerMenu, showOfficeMenu, showAppointmentMenu, showAboutMenu, showTeamMenu
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
            showOptions("Menu Principal", options, optionsStyles, size);
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


void showAboutMenu() {
    showGenericInfo("--------------------------------------------- Sobre ---------------------------------------------\n| O projeto desenvolvido é um sistema de agendamento para uma advocacia, criado em linguagem C. |\n| Ele tem como principal funcionalidade o agendamento de reuniões entre clientes e advogados,   |\n| facilitando a organização dos atendimentos. Este trabalho é uma tarefa realizada para a       |\n| disciplina de Programação do curso de Bacharelado em Sistemas de Informação na UFRN.          |\n-------------------------------------------------------------------------------------------------\n");
}

void showTeamMenu() {
    showGenericInfo("--------------------------------------------- Equipe ---------------------------------------------\n| O projeto foi feitos pelos alunos do curso de Bachalerado em Sistemas de Informação na UFRN:   |  \n|                                                                                                |\n| - Mosiah Adam Maria de Araújo: https://github.com/akemi-adam                                   |\n| - Felipe Erik: https://github.com/zfelip                                                       |\n--------------------------------------------------------------------------------------------------\n");   
}