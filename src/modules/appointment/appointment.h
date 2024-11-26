#ifndef APPOINTMENT
#define APPOINTMENT

#include "./../../utils/date.h"

typedef struct Appointment {
    int clientId;
    int lawyerId;
    int officeId;
    Datetime startDate;
    Datetime endDate;
} Appointment;

void showAppointmentMenu(void);

void createAppointment(void);

void readAppointment(void);

void listAppointments(void);

void updateAppointment(void);

void deleteAppointment(void);

#endif