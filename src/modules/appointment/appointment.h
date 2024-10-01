#ifndef APPOINTMENT
#define APPOINTMENT

#include "./../../utils/date.h"

typedef struct Schedule {
    Datetime *startDate;
    Datetime *endDate;
} Schedule;

typedef struct Appointment {
    int clientId;
    int lawyerId;
    int officeId;
    Schedule *schedule;
} Appointment;

#endif