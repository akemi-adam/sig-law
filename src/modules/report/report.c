#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "./../../utils/interfaces.h"
#include "./../../utils/validation.h"
#include "./../../utils/storage.h"
#include "./../../utils/date.h"
#include "./../../utils/str.h"
#include "./report.h"
#include "../client/client.h"
#include "../lawyer/lawyer.h"
#include "../office/office.h"
#include "../appointment/appointment.h"
#include "../person/person.h"

#ifdef __unix__

#include <termios.h>
#include <unistd.h>


/**
 * Relatórios
 * 
 * @return void
 * 
 * Authors:
 *  - ChatGPT, Adaptado por https://github.com/veraxqy
 */

// Estrutura para lista encadeada
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// Funções para manipular listas encadeadas
Node* createNode(void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node **head, void *data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

Node* sortLawyersAlphabetically(Node *head) {
    if (head == NULL || head->next == NULL) return head;

    Node *sorted = NULL;

    while (head != NULL) {
        Node *current = head;
        head = head->next;

        if (sorted == NULL || strcmp(((Lawyer *)current->data)->person.name, ((Lawyer *)sorted->data)->person.name) < 0) {
            // Inserir no início da lista ordenada
            current->next = sorted;
            sorted = current;
        } else {
            // Encontrar a posição correta para inserir
            Node *temp = sorted;
            while (temp->next != NULL && strcmp(((Lawyer *)temp->next->data)->person.name, ((Lawyer *)current->data)->person.name) <= 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    return sorted;
}

void showReportMenu() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
    #endif
    int option = 0, size = 5;
    bool isSelected = false, loop = true;
    char optionsStyles[size][11];
    char options[5][30] = {
        "1. Relatório Advogados", "2. Relatório Clientes", "3. Relatório Escritórios", "4. Relatório Agendamentos",
        "5. Voltar"
    };
    void (*actions[])() = {
        reportLawyer, reportClient, reportOffice, reportAppointment
    };
    setOptionsStyle(optionsStyles, size);
    while (loop) {
        #ifdef __unix__
            system("clear");
            enableRawMode();
        #else
            system("cls");
        #endif
        if (!isSelected) {
            showOptions("Menu Relatório", options, optionsStyles, size);
            strcpy(optionsStyles[option], RESET_STYLE);
            selectOption(&option, size - 1, &isSelected);
            strcpy(optionsStyles[option], CYAN_STYLE);
        } else {
            #ifdef __unix__
                disableRawMode(&originalTerminal);
            #endif
            isSelected = false;
            if (option >= 0 && option <= (size - 2)) {
                actions[option](); 
            } else {
                loop = false;
            }
        }
    }
}

void reportLawyer() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
    #endif
    int option = 0, size = 3;
    bool isSelected = false, loop = true;
    char optionsStyles[size][11];
    char options[3][30] = {
        "1. Ordem Alfabética", "2. Número de Clientes", "3. Voltar"
    };
    void (*actions[])() = {
        lawyerAlphabeticalOrder, lawyerMoreClient
    };
    setOptionsStyle(optionsStyles, size);
    while (loop) {
        #ifdef __unix__
            system("clear");
            enableRawMode();
        #else
            system("cls");
        #endif
        if (!isSelected) {
            showOptions("Menu Relatório Advogado", options, optionsStyles, size);
            strcpy(optionsStyles[option], RESET_STYLE);
            selectOption(&option, size - 1, &isSelected);
            strcpy(optionsStyles[option], CYAN_STYLE);
        } else {
            #ifdef __unix__
                disableRawMode(&originalTerminal);
            #endif
            isSelected = false;
            if (option >= 0 && option <= (size - 2)) {
                actions[option](); 
            } else {
                loop = false;
            }
        }
    }
}

void lawyerAlphabeticalOrder() {
    Node *lawyersList = NULL;
    int count_lawyers;
    Lawyer *lawyers = getLawyers(&count_lawyers);

    for (int i = 0; i < count_lawyers; i++) {
        Lawyer *newLawyer = (Lawyer *)malloc(sizeof(Lawyer));
        *newLawyer = lawyers[i];
        appendNode(&lawyersList, newLawyer);
    }

    lawyersList = sortLawyersAlphabetically(lawyersList);

    printf("--------- Relatório ---------\n");
    printf("--------- Advogados ---------\n");

    int index = 0;
    Node *current = lawyersList;
    while (current != NULL) {
        Lawyer *lawyer = (Lawyer *)current->data;
        printf("ID: %d - Nome: %s\n", index + 1, lawyer->person.name);
        current = current->next;
        index++;
    }

    current = lawyersList;
    while (current != NULL) {
        Node *temp = current;
        free((Lawyer *)current->data);
        current = current->next;
        free(temp);
    }

    free(lawyers);

    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

void lawyerMoreClient() {
    Node *lawyersList = NULL;
    int count_lawyers;
    Lawyer *lawyers = getLawyers(&count_lawyers);

    int count_clients;
    Client *clients = getClients(&count_clients);

    int count_appointments;
    Appointment *appointments = getAppointments(&count_appointments);

    int *client_counts = (int *)calloc(count_lawyers, sizeof(int));
    int total_unique_clients = 0;

    for (int i = 0; i < count_lawyers; i++) {
        int *unique_clients = (int *)calloc(count_clients, sizeof(int));

        for (int j = 0; j < count_appointments; j++) {
            if (!appointments[j].isDeleted && appointments[j].lawyerId == (i+1)) {
                int clientId = appointments[j].clientId;

                if (unique_clients[clientId] == 0) {
                    unique_clients[clientId] = 1;
                    client_counts[i]++;
                }
            }
        }
        Lawyer *newLawyer = (Lawyer *)malloc(sizeof(Lawyer));
        *newLawyer = lawyers[i];
        appendNode(&lawyersList, newLawyer);

        free(unique_clients);
    }

    for (int i = 0; i < count_lawyers; i++) {
        total_unique_clients += client_counts[i];
    }

    printf("---------- Relatório ---------\n");
    printf("---- Advogados & Clientes ----\n");

    if (count_appointments == 0 || count_lawyers == 0 || count_clients == 0) {
        printf("Os dados são insuficientes para gerar um relatório.\n");
    } else {
        Node *current = lawyersList;
        int index = 0;
        while (current != NULL) {
            Lawyer *lawyer = (Lawyer *)current->data;
            printf("Advogado: %s (ID: %d) - Número de clientes: %d\n", lawyer->person.name, (index+1), client_counts[index]);
            printf("------------------------------------------------------------------\n");
            current = current->next;
            index++;
        }
        printf("Total de Clientes: %d\n", count_clients);
        printf("------------------------------------------------------------------\n");
    }
    
    Node *current = lawyersList;
    while (current != NULL) {
        Node *temp = current;
        free((Lawyer *)current->data);
        current = current->next;
        free(temp);
    }

    free(client_counts);
    free(lawyers);
    free(clients);
    free(appointments);

    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

void reportClient() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
    #endif
    int option = 0, size = 2;
    bool isSelected = false, loop = true;
    char optionsStyles[size][11];
    char options[2][30] = {
        "1. Número de Agendamentos", "2. Voltar"
    };
    void (*actions[])() = {
        clientAppointment
    };
    setOptionsStyle(optionsStyles, size);
    while (loop) {
        #ifdef __unix__
            system("clear");
            enableRawMode();
        #else
            system("cls");
        #endif
        if (!isSelected) {
            showOptions("Menu Relatório Cliente", options, optionsStyles, size);
            strcpy(optionsStyles[option], RESET_STYLE);
            selectOption(&option, size - 1, &isSelected);
            strcpy(optionsStyles[option], CYAN_STYLE);
        } else {
            #ifdef __unix__
                disableRawMode(&originalTerminal);
            #endif
            isSelected = false;
            if (option >= 0 && option <= (size - 2)) {
                actions[option](); 
            } else {
                loop = false;
            }
        }
    }
}

void clientAppointment() {
    int count_clients;
    Client *clients = getClients(&count_clients);

    int count_appointments;
    Appointment *appointments = getAppointments(&count_appointments);

    int *appointments_counts = (int *)calloc(count_clients, sizeof(int));

    for (int i = 0; i < count_appointments; i++) {
        if (!appointments[i].isDeleted) {
            int clientId = appointments[i].clientId;

            for (int j = 0; j < count_clients; j++) {
                if ((j+1) == clientId) {
                    appointments_counts[j]++;
                    break;
                }
            }
        }
    }

    printf("---------- Relatório ----------\n");
    printf("--- Clientes & Agendamentos ---\n");

    if (count_appointments == 0 || count_clients == 0) {
        printf("Os dados são insuficientes para gerar um relatório.\n");
    }
    
    for(int i = 0; i < count_clients; i++) {
        printf("Cliente: %s (ID: %d) - Número de Agendamentos: %d\n", clients[i].person.name, (i+1), appointments_counts[i]);
        printf("------------------------------------------------------------------\n");
    }

    printf("Total de Agendamentos: %d\n", count_appointments);
    printf("------------------------------------------------------------------\n");

    free(appointments_counts);
    free(clients);
    free(appointments);

    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

void reportOffice() {
    int count_lawyers;
    Lawyer *lawyers = getLawyers(&count_lawyers);

    int count_offices;
    Office *offices = getOffices(&count_offices);

    int count_appointments;
    Appointment *appointments = getAppointments(&count_appointments);

    int *lawyers_counts = (int *)calloc(count_offices, sizeof(int));

    for (int i = 0; i < count_offices; i++) {
        int *unique_lawyers = (int *)calloc(count_offices, sizeof(int));

        for (int j = 0; j < count_appointments; j++) {
            if (!appointments[j].isDeleted && appointments[j].officeId == (i+1)) {
                int lawyerId = appointments[j].lawyerId;

                if (unique_lawyers[lawyerId] == 0) {
                    unique_lawyers[lawyerId] = 1;
                    lawyers_counts[i]++;
                }
            }
        }

        free(unique_lawyers);
    }

    printf("---------- Relatório ----------\n");
    printf("--- Escritórios & Advogados ---\n");

    if (count_appointments == 0 || count_lawyers == 0 || count_offices == 0) {
        printf("Os dados são insuficientes para gerar um relatório.\n");
    }
    
    for(int i = 0; i < count_offices; i++) {
        printf("Escritório: %s (ID: %d) - Número de Advogados Associados: %d\n", offices[i].address, (i+1), lawyers_counts[i]);
        printf("------------------------------------------------------------------\n");
    }

    printf("Total de Escritórios: %d\n", count_offices);
    printf("------------------------------------------------------------------\n");

    free(lawyers_counts);
    free(lawyers);
    free(offices);
    free(appointments);

    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

void reportAppointment() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
    #endif
    int option = 0, size = 4;
    bool isSelected = false, loop = true;
    char optionsStyles[size][11];
    char options[4][30] = {
        "1. Agendamentos de Hoje", "2. Agendamentos Finalizados", "3. Agendamentos Próximos",
        "4. Voltar"
    };
    void (*actions[])() = {
        appointmentToday, appointmentPast, appointmentUpcoming
    };
    setOptionsStyle(optionsStyles, size);
    while (loop) {
        #ifdef __unix__
            system("clear");
            enableRawMode();
        #else
            system("cls");
        #endif
        if (!isSelected) {
            showOptions("Menu Relatório Agendamento", options, optionsStyles, size);
            strcpy(optionsStyles[option], RESET_STYLE);
            selectOption(&option, size - 1, &isSelected);
            strcpy(optionsStyles[option], CYAN_STYLE);
        } else {
            #ifdef __unix__
                disableRawMode(&originalTerminal);
            #endif
            isSelected = false;
            if (option >= 0 && option <= (size - 2)) {
                actions[option](); 
            } else {
                loop = false;
            }
        }
    }
}

/**
 * Relatórios Agendamentos
 * 
 * @return void
 * 
 * Authors:
 *  - ChatGPT, Adaptado por https://github.com/veraxqy
 */
void appointmentToday() {
    int count_appointments;
    Appointment *appointments = getAppointments(&count_appointments);

    time_t now = time(NULL);
    struct tm tm = *localtime(&now);

    char today[11];
    snprintf(today, sizeof(today), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon +1, tm.tm_year + 1900);

    printf("---------- Relatório ----------\n");
    printf("------ Agendamentos Hoje ------\n");
    bool found = false;

    for (int i = 0; i < count_appointments; i++) {
        if (!appointments[i].isDeleted && strcmp(appointments[i].startDate.onlyDate, today) == 0) {
            found = true;
            printf("ID: %d\nCódigo Cliente: %d\nCódigo Advogado: %d\nCódigo Escritório: %d\nData início: %s\nData término: %s\n", i + 1, appointments[i].clientId, appointments[i].lawyerId, appointments[i].officeId, appointments[i].startDate.date, appointments[i].endDate.date);
            printf("------------------------------------------------------------------\n");
        }
    }

    if (!found) {
        printf("Não há nenhum agendamento marcado para o dia de hoje!\n");
    }

    free(appointments);

    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

void appointmentPast() {
    int count_appointments;
    Appointment *appointments = getAppointments(&count_appointments);

    time_t now = time(NULL);

    printf("---------- Relatório -----------\n");
    printf("--- Agendamentos Finalizados ---\n");
    bool found = false;

    for (int i = 0; i < count_appointments; i++) {
        if (!appointments[i].isDeleted) {
            struct tm endDateTime = {0};
            strptime(appointments[i].endDate.date, "%d/%m/%Y %H:%M", &endDateTime);
            time_t appointmentEndTime = mktime(&endDateTime);

            if (difftime(appointmentEndTime, now) < 0) {
                found = true;
                printf("ID: %d\nCódigo Cliente: %d\nCódigo Advogado: %d\nCódigo Escritório: %d\nData início: %s\nData término: %s\n", i + 1, appointments[i].clientId, appointments[i].lawyerId, appointments[i].officeId, appointments[i].startDate.date, appointments[i].endDate.date);
                printf("------------------------------------------------------------------\n");
            }
        }
    }

    if (!found) {
        printf("Não há nenhum agendamento finalizado!\n");
    }

    free(appointments);

    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

void appointmentUpcoming() {
    int count_appointments;
    Appointment *appointments = getAppointments(&count_appointments);

    time_t now = time(NULL);

    printf("---------- Relatório ----------\n");
    printf("---- Agendamentos Próximos ----\n");
    bool found = false;

    for (int i = 0; i < count_appointments; i++) {
        if (!appointments[i].isDeleted) {
            struct tm endDateTime = {0};
            strptime(appointments[i].endDate.date, "%d/%m/%Y %H:%M", &endDateTime);
            time_t appointmentEndTime = mktime(&endDateTime);

            if (difftime(appointmentEndTime, now) > 0) {
                found = true;
                printf("ID: %d\nCódigo Cliente: %d\nCódigo Advogado: %d\nCódigo Escritório: %d\nData início: %s\nData término: %s\n", i + 1, appointments[i].clientId, appointments[i].lawyerId, appointments[i].officeId, appointments[i].startDate.date, appointments[i].endDate.date);
                printf("------------------------------------------------------------------\n");
            }
        }
    }

    if (!found) {
        printf("Não há nenhum agendamento próximo!\n");
    }

    free(appointments);

    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

#endif