#include "interfaces.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

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
 */
void disableRawMode(struct termios *originalTerminal) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, originalTerminal);
}

/*
 * Incrementa ou decrementa um inteiro ao pressionar as teclas de Down-Arrow ou Up-Arrow
 *
 * Inputs:
 *  - int *option: Um ponteiro de inteiro que representa a opção escolhida no menu
 *  - int optionsAmount: Quantidade máxima de opções do menu
 *
 * Outputs: Void
 */
void selectOption(int *option, int optionsAmount) {
    char buf[3];
    if (read(STDIN_FILENO, buf, 1) == 1) {
        if (buf[0] == '\033') {
            if (read(STDIN_FILENO, buf + 1, 1) == 1 && read(STDIN_FILENO, buf + 2, 1) == 1) {
                if (buf[1] == '[') {
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
    }
}

void showMainMenu() {
    //
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
