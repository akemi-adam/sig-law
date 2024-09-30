#ifndef APPOINTMENT
#define APPOINTMENT

#include "./../../utils/date.h"

struct Schedule {
    Datetime *startDate;
    Datetime *endDate;
};

struct Appointment {
    int clientId;
    int lawyerId;
    int officeId;
    Schedule *schedule;
};

#endif