#ifndef INTERFACES
#define INTERFACES
#include <termios.h>

void enableRawMode(void);

void showMainMenu(void);

void showClientMenu(void);

void showLawyerMenu(void);

void showOfficeMenu(void);

void showAppointmentMenu(void);

void print(char[]);

#endif