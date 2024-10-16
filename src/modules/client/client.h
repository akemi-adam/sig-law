#ifndef CLIENT
#define CLIENT

#include "./../person/person.h"

struct Client {
    struct Person *person;
};

void showClientMenu(void);

void createClient(void);

void readClient(void);

void listClients(void);

void updateClient(void);

void deleteClient(void);

#endif
