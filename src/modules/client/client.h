#ifndef CLIENT
#define CLIENT

#include "./../person/person.h"

typedef struct Client {
    Person person;
} Client;

void showClientMenu(void);

void createClient(void);

void readClient(void);

void listClients(void);

void updateClient(void);

void deleteClient(void);

#endif
