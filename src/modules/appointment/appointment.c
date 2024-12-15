#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./../../utils/interfaces.h"
#include "./../../utils/validation.h"
#include "./../../utils/storage.h"
#include "./../../utils/date.h"
#include "./../../utils/str.h"
#include "./appointment.h"
#include "./../client/client.h"
#include "./../lawyer/lawyer.h"
#include "./../office/office.h"


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
    Appointment appointment;
    int tempId;
    char date[11], startTime[6], endTime[6], clientId[6], lawyerId[6], officeId[6];

    Validation idRules[3] = {validateRequired, validateNumber, validatePositive},
        dateRules[2] = {validateRequired, validateDate},
        hourRules[2] = {validateRequired, validateHour};
        
    printf("---- Cadastrar Agendamento ----\n");
    readStrField(clientId, "Código do Cliente", 6, idRules, 3);
    parseInt(clientId, &tempId);
    Client *client = findClient(tempId);
    if (client == NULL) {
        free(client);
        printf("Cliente não encontrado!\n");
        proceed();
        return;
    }
    free(client);

    readStrField(lawyerId, "Código do Advogado", 6, idRules, 3);
    parseInt(lawyerId, &tempId);
    Lawyer *lawyer = findLawyer(tempId);
    if (lawyer == NULL) {
        free(lawyer);
        printf("Advogado não encontrado!\n");
        proceed();
        return;
    }
    free(lawyer);

    readStrField(officeId, "Código do Escritório", 6, idRules, 3);
    parseInt(officeId, &tempId);
    Office *office = findOffice(tempId);
    if (office == NULL) {
        free(office);
        printf("Escritório não encontrado!\n");
        proceed();
        return;
    }
    free(office);

    readStrField(date, "Data (dd/mm/aaaa)", 11, dateRules, 2);
    readStrField(startTime, "Horário do início da consulta (hh:mm)", 6, hourRules, 2);
    readStrField(endTime, "Horário do término da consulta (hh:mm)", 6, hourRules, 2);
    loadDatetime(&appointment.startDate, date, startTime);
    loadDatetime(&appointment.endDate, date, endTime);

    parseInt(clientId, &appointment.clientId);
    parseInt(lawyerId, &appointment.lawyerId);
    parseInt(officeId, &appointment.officeId);
    saveFile(&appointment, sizeof(Appointment), "appointments.dat");

    bool status = addElementToFile(&appointment, sizeof(Appointment), "appointments.dat");

    printf("\n%s\n", status ? "Agendamento cadastrado com sucesso!\nPressione <Enter> para prosseguir..." : "Houve um erro ao cadastrar o agendamento!");
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
    Appointment *appointment = (Appointment*) malloc(sizeof(Appointment));
    readFile(appointment, sizeof(Appointment), "appointments.dat");
    printf("---- Listar Agendamentos ----\n");
    printf("------------------------------------------------------------------\n");
    printf("ID: %d\nCódigo Cliente: %d\nCódigo Advogado: %d\nCódigo Escritório: %d\nData: %s\n", 1, appointment->clientId, appointment->lawyerId, appointment->officeId, appointment->startDate.date);
    free(appointment);
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
    char id[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive};
    printf("---- Buscar Agendamento ----\n");
    readStrField(id, "Código do Agendamento", 6, idRules, 3);
    printf("------------------------------------------------------------------\n");
    printf("ID: %s\nCódigo Cliente: %d\nCódigo Advogado: %d\nCódigo Escritório: %d\nData: %s\nHorário: %s\n", id, 1, 1, 1, "", "");
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
    Appointment appointment;
    char date[11], startTime[6], endTime[6], appointmentId[6], clientId[6], lawyerId[6], officeId[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive},
        dateRules[2] = {validateRequired, validateDate},
        hourRules[2] = {validateRequired, validateHour};
    
    printf("---- Atualizar Agendamento ----\n");
    readStrField(appointmentId, "Código do Agendamento", 6, idRules, 3);
    readStrField(clientId, "Código do Cliente", 6, idRules, 3);
    readStrField(lawyerId, "Código do Advogado", 6, idRules, 3);
    readStrField(officeId, "Código do Escritório", 6, idRules, 3);
    readStrField(date, "Data (dd/mm/aaaa)", 11, dateRules, 2);
    readStrField(startTime, "Horário do início da consulta (hh:mm)", 6, hourRules, 2);
    readStrField(endTime, "Horário do término da consulta (hh:mm)", 6, hourRules, 2);
    loadDatetime(&appointment.startDate, date, startTime);
    loadDatetime(&appointment.endDate, date, endTime);

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
    char id[6];
    Validation idRules[3] = {validateRequired, validateNumber, validatePositive};
    printf("---- Deletar Agendamento ----\n");
    readStrField(id, "Código do Agendamento", 6, idRules, 3);
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

/**
 * Retorna uma lista contendo todos os agendamentos
 * 
 * @param int *officesNumber: Número de agendamentos cadastrados
 * 
 * @return Office*: endereço da lista de agendamentos
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
Appointment* getAppointments(int *officesNumber) {
    const size_t structSize = sizeof(Appointment);
    *officesNumber = getNumberOfElements("appointments.dat", structSize);
    Appointment *appointments = (Appointment*) malloc(structSize * (*officesNumber));
    readFile(appointments, structSize, *officesNumber, "appointments.dat");

    return appointments;
}

/**
 * Retorna um agendamento específico a partir de seu ID
 * 
 * @param const char *id: ID a ser procurado
 * 
 * @return Appointment*|NULL: Agendamento correspondente ao ID | NULL, caso não encontre
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
Appointment* findAppointment(int id) {
    int count;
    id--;

    Appointment* appointments = getAppointments(&count);
    if (!appointments || id < 0 || id >= count) {
        free(appointments);
        return NULL;
    }

    if (appointments[id].isDeleted) {
        free(appointments);
        return NULL;
    }

    Appointment* appointment = (Appointment*) malloc(sizeof(Appointment));

    *appointment = appointments[id];
    free(appointments);

    return appointment;
}


/**
 * Edita/atualiza a lista de agendamentos no arquivo
 * 
 * @param int id: ID do agendamento
 * @param Appointment *appointment: Agendamento
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void editAppointments(int id, Appointment *appointment) {
    int count;
    Appointment *appointments = getAppointments(&count);
    appointments[id - 1] = *appointment;
    saveFile(appointments, sizeof(Appointment), count, "appointments.dat");
    free(appointments);
}
