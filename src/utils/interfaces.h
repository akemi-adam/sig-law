#ifndef INTERFACES
#define INTERFACES
#define CYAN_STYLE "\033[0;36m"
#define RESET_STYLE "\033[0m"

#include <stdbool.h>


#ifdef __unix__

#include <termios.h>

void enableRawMode(void);

void disableRawMode(struct termios*);

#endif


void readline(char[], int);

void selectOption(int*, int, bool*);

void setOptionsStyle(char[][11], int);

void showOptions(char[], char[][30], char[][11], int);

bool proceed();

void showGenericInfo(char[]);

void showMainMenu(void);

void showAboutMenu(void);

void showTeamMenu(void);

#endif
