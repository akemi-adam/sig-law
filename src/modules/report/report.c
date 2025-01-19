#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
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
 *  - https://github.com/akemi-adam
 */

void showReportMenu() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
    #endif
    int option = 0, size = 4;
    bool isSelected = false, loop = true;
    char optionsStyles[size][11];
    char options[4][30] = {
        "1. Relatório Advogados", "2. Relatório Clientes", "3. Relatório Escritórios",
        "4. Voltar"
    };
    void (*actions[])() = {
        reportLawyer, reportClient, reportOffice
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
            showOptions("Menu Cliente", options, optionsStyles, size);
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
    int count_lawyers;
    Lawyer *lawyers = getLawyers(&count_lawyers);

    int count_clients;
    Client *clients = getClients(&count_clients);

    int count_appointments;
    Appointment *appointments = getAppointments(&count_appointments);

    int *client_counts = (int *)calloc(count_lawyers, sizeof(int));

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

        free(unique_clients);
    }

    printf("---------- Relatório ---------\n");
    printf("---- Advogados & Clientes ----\n");

    if (count_appointments == 0 || count_lawyers == 0 || count_clients == 0) {
        printf("Os dados são insuficientes para gerar um relatório.\n");
    }
    
    for(int i = 0; i < count_lawyers; i++) {
        printf("Advogado: %s (ID: %d) - Número de clientes: %d\n", lawyers[i].person.name, (i+1), client_counts[i]);
    }

    free(client_counts);
    free(lawyers);
    free(clients);
    free(appointments);

    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

void reportClient() {
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
    }

    free(appointments_counts);
    free(clients);
    free(appointments);

    printf("Pressione <Enter> para prosseguir...\n");
    proceed();

}

void reportOffice() {
    printf("Relatório Escritórios");
}

#endif