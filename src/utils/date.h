#ifndef DATE
#define DATE

typedef struct Datetime {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    char date[18];
    char onlyDate[11];
    char time[6];
} Datetime;

void loadDatetime(Datetime*, const char*, const char*);

#endif