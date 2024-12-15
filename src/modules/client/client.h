#ifndef CLIENT
#define CLIENT

#include <stdbool.h>
#include "./../person/person.h"

typedef struct Client {
    int id;
    Person person;
    bool isDeleted;
} Client;

void showClientMenu(void);

void createClient(void);

void readClient(void);

void listClients(void);

void updateClient(void);

void deleteClient(void);

Client* getClients(int*);

Client* findClient(int);

void editClients(int, Client*);

#endif
