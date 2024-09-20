#ifndef INTERFACES
#define INTERFACES

#include <stdbool.h>

#define CYAN_UNDERLINE_TEXT "\e[4;36m"
#define RESET_STYLE "\e[0m"

#ifdef __unix__

#include <termios.h>

void enableRawMode(void);

void disableRawMode(struct termios*);

#endif

void selectOption(int*, int, bool*);

void setOptionsStyle(char[][30], int);

void showMainMenu(void);

void showClientMenu(void);

void showLawyerMenu(void);

void showOfficeMenu(void);

void showAppointmentMenu(void);

void print(char[]);

#endif
