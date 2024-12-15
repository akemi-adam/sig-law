#include "./date.h"
#include "./str.h"
#include <stdio.h>
#include <string.h>

/**
 * Carrega uma data e horário em uma struct Datetime
 * 
 * @param Datetime *datetime
 * @param const char date[11]
 * @param const char time[6]
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void loadDatetime(Datetime *datetime, const char *date, const char *time) {
    char strYear[5], strMonth[3], strDay[3], strHour[3], strMinute[3];
    
    strncpy(strDay, date, 2);
    strncpy(strMonth, date + 3, 2);
    strncpy(strYear, date + 6, 4);
    strncpy(strHour, time, 2);
    strncpy(strMinute, time + 3, 2);

    strcpy(datetime->onlyDate, date);
    strcpy(datetime->time, time);

    parseInt(strYear, &datetime->year);
    parseInt(strMonth, &datetime->month);
    parseInt(strDay, &datetime->day);
    parseInt(strHour, &datetime->hour);
    parseInt(strMinute, &datetime->minute);

    sprintf(datetime->date, "%s %s", date, time);
}