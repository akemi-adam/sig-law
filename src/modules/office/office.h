#ifndef OFFICE
#define OFFICE

#include <stdbool.h>

typedef struct Office {
    int id;
    char address[100];
    bool isDeleted;
} Office ;

void showOfficeMenu(void);

void createOffice(void);

void readOffice(void);

void listOffices(void);

void updateOffice(void);

void deleteOffice(void);

Office* getOffices(int*);

Office* findOffice(int);

void editOffices(int, Office*);

#endif
