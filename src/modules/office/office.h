#ifndef OFFICE
#define OFFICE

typedef struct Office {
    int id;
    char address[100];
} Office ;

void showOfficeMenu(void);

void createOffice(void);

void readOffice(void);

void listOffices(void);

void updateOffice(void);

void deleteOffice(void);

#endif
