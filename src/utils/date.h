#ifndef DATE
#define DATE

typedef struct Datetime {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    char *date; // DD/MM/YYYY HH:MM
} Datetime;

#endif