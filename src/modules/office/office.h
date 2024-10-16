#ifndef OFFICE
#define OFFICE

struct Office {
    int id;
    char address[100];
};

void showOfficeMenu(void);

void createOffice(void);

void readOffice(void);

void listOffices(void);

void updateOffice(void);

void deleteOffice(void);

#endif