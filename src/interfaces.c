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

void selectOption(int *option, int optionAmount) {
    char buf[3];
    if (read(STDIN_FILENO, buf, 1) == 1) {
        if (buf[0] == '\033') {
            if (read(STDIN_FILENO, buf + 1, 1) == 1 && read(STDIN_FILENO, buf + 2, 1) == 1) {
                if (buf[1] == '[') {
                    switch (buf[2]) {
                        case 'A':
                            *option = (*option > 0) ? *option - 1 : optionAmount;
                            break;
                        case 'B':
                            *option = (*option < optionAmount) ? *option + 1 : 0;
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
