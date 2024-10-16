#ifndef LAWYER
#define LAWYER

#include "./../person/person.h"

struct Lawyer {
    struct Person *person;
    char cna[13];
};

void showLawyerMenu(void);

void createLawyer(void);

void readLawyer(void);

void listLawyers(void);

void updateLawyer(void);

void deleteLawyer(void);

#endif