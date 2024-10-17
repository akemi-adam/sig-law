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

/**
 * Formulário para cadastrar um agendamento
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void createAppointment() {
    Appointment *appointment = (Appointment*) malloc(sizeof(Appointment));
    appointment->schedule = (Schedule*) malloc(sizeof(Schedule));
    appointment->schedule->endDate = (Datetime*) malloc(sizeof(Datetime));
    appointment->schedule->startDate = (Datetime*) malloc(sizeof(Datetime));
    char date[11], startTime[6], endTime[6];

    printf("---- Cadastrar Agendamento ----\n");
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

    printf("\nAgendamento cadastrado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Lista todos os agendamentos do sistema
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void listAppointments() {
    printf("---- Listar Agendamentos ----\n");
    printf("------------------------------------------------------------------\n");
    printf("ID: %d\nCódigo Cliente: %d\nCódigo Advogado: %d\nCódigo Escritório: %d\nData: %s\nHorário: %s\n", 1, 1, 1, 1, "", "");
    printf("------------------------------------------------------------------\n");
    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Exibe os dados de um agendamento específico
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void readAppointment() {
    int id;
    printf("---- Buscar Agendamento ----\nCódigo do Agendamento: ");
    scanf("%d", &id);
    printf("------------------------------------------------------------------\n");
    printf("ID: %d\nCódigo Cliente: %d\nCódigo Advogado: %d\nCódigo Escritório: %d\nData: %s\nHorário: %s\n", id, 1, 1, 1, "", "");
    printf("------------------------------------------------------------------\n");
    printf("Pressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Formulário para atualizar os dados de um agendamento específico
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void updateAppointment() {
    Appointment *appointment = (Appointment*) malloc(sizeof(Appointment));
    appointment->schedule = (Schedule*) malloc(sizeof(Schedule));
    appointment->schedule->endDate = (Datetime*) malloc(sizeof(Datetime));
    appointment->schedule->startDate = (Datetime*) malloc(sizeof(Datetime));
    char date[11], startTime[6], endTime[6];
    int id;

    printf("---- Cadastrar Agendamento ----\nCódigo do Agendamento: ");
    scanf("%d", &id);

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

    printf("\nAgendamento editado com sucesso!\nPressione <Enter> para prosseguir...\n");
    proceed();
}

/**
 * Deleta um agendamento
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void deleteAppointment() {
    int id;
    printf("---- Deletar Agendamento ----\nCódigo do Agendamento: ");
    scanf("%d", &id);
    printf("Agendamento deletado com sucesso!\nPressione <Enter> para prosseguir...\n");
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
