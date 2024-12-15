#ifndef LAWYER
#define LAWYER

#include <stdbool.h>
#include "./../person/person.h"

typedef struct Lawyer {
    int id;
    Person person;
    char cna[13];
    bool isDeleted;
} Lawyer;

void showLawyerMenu(void);

void createLawyer(void);

void readLawyer(void);

void listLawyers(void);

void updateLawyer(void);

void deleteLawyer(void);

Lawyer* getLawyers(int*);

Lawyer* findLawyer(int);

void editLawyers(int, Lawyer*);

#endif
