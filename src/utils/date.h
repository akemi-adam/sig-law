#ifndef DATE
#define DATE

typedef struct Datetime {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    char date[17];
} Datetime;

void loadDatetime(Datetime*, const char[11], const char[6]);

#endif