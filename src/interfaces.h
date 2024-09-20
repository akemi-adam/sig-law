#ifndef INTERFACES
#define INTERFACES
#define CYAN_UNDERLINE_TEXT "\e[4;36m"
#define RESET_STYLE "\e[0m"
#include <termios.h>

void enableRawMode(void);

void disableRawMode(struct termios*);

void selectOption(int*, int);

void showMainMenu(void);

void showClientMenu(void);

void showLawyerMenu(void);

void showOfficeMenu(void);

void showAppointmentMenu(void);

void print(char[]);

#endif
