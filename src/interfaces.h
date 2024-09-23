#ifndef INTERFACES
#define INTERFACES
#define CYAN_UNDERLINE_TEXT "\e[4;36m"
#define RESET_STYLE "\e[0m"

#include <stdbool.h>


#ifdef __unix__

#include <termios.h>

void enableRawMode(void);

void disableRawMode(struct termios*);

#endif


void selectOption(int*, int, bool*);

void setOptionsStyle(char[][11], int);

bool proceed();

void showMainMenu(void);

void showClientMenu(void);

void showLawyerMenu(void);

void showOfficeMenu(void);

void showAppointmentMenu(void);

void showAboutMenu(void);

void showTeamMenu(void);

#endif
