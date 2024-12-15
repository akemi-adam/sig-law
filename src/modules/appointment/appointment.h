#ifndef APPOINTMENT
#define APPOINTMENT

#include <stdbool.h>
#include "./../../utils/date.h"

typedef struct Appointment {
    int id;
    int clientId;
    int lawyerId;
    int officeId;
    Datetime startDate;
    Datetime endDate;
    bool isDeleted;
} Appointment;

void showAppointmentMenu(void);

void createAppointment(void);

void readAppointment(void);

void listAppointments(void);

void updateAppointment(void);

void deleteAppointment(void);

Appointment* getAppointments(int*);

Appointment* findAppointment(int);

void editAppointments(int, Appointment*);

#endif