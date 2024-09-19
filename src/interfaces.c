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
