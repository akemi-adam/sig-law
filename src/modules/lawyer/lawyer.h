#ifndef LAWYER
#define LAWYER

#include "./../person/person.h"

struct Lawyer {
    struct Person *person;
    char cna[13];
};

#endif