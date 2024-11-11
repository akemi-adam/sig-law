#ifndef LAWYER
#define LAWYER

#include "./../person/person.h"

typedef struct Lawyer {
    Person person;
    char cna[13];
} Lawyer;

void showLawyerMenu(void);

void createLawyer(void);

void readLawyer(void);

void listLawyers(void);

void updateLawyer(void);

void deleteLawyer(void);

#endif
