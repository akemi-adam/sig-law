#include "usecases.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./../../utils/interfaces.h"
#include "./../../utils/date.h"
#include "appointment.h"

#ifdef __unix__

#include <termios.h>
#include <unistd.h>

#endif

void createAppointment() {
    Appointment *appointment = malloc(sizeof(Appointment));
    appointment->schedule = malloc(sizeof(Schedule));
    appointment->schedule->endDate = malloc(sizeof(Datetime));
    appointment->schedule->startDate = malloc(sizeof(Datetime));
    char date[11], startTime[6], endTime[6];

    printf("---- Cadastrar Advogado ----\n");
    printf("Código do Cliente: ");
    scanf("%d", &appointment->clientId);

    printf("Código do Advogado: ");
    scanf("%d", &appointment->lawyerId);

    printf("Código do Escritório: ");
    scanf("%d", &appointment->officeId);
    flushInput();

    printf("Data (dd/mm/aaaa): ");
    readline(date, 11);

    printf("Horário do início da consulta (hh:mm): ");
    readline(startTime, 11);

    printf("Horário do término da consulta (hh:mm): ");
    readline(endTime, 11);

    free(appointment->schedule->startDate);
    free(appointment->schedule->endDate);
    free(appointment->schedule);
    free(appointment);

    printf("\nUsuário cadastrado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Exibe o menu do módulo agendamento e que pede para o usuário selecionar uma opção
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void showAppointmentMenu() {
    #ifdef __unix__
        struct termios originalTerminal;
        tcgetattr(STDIN_FILENO, &originalTerminal);
    #endif
    int option = 0, size = 6;
    bool isSelected = false, loop = true;
    char optionsStyles[size][11];
    char options[6][30] = {
        "1. Cadastrar Agendamento", "2. Mostrar Agendamentos", "3. Achar Agendamento",
        "4. Editar Agendamento", "5. Excluir Agendamento", "6. Voltar"
    };
    void (*actions[])() = {
        createAppointment, listAppointments, readAppointment, updateAppointment, deleteAppointment
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
            showOptions("Menu Agendamento", options, optionsStyles, size);
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