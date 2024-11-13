#include "./date.h"
#include <string.h>

/**
 * Carrega uma data e horário em uma struct Datetime
 * 
 * @param Datetime* datetime
 * @param const char date[11]
 * @param const char time[6]
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void loadDatetime(Datetime* datetime, const char date[11], const char time[6]) {
    int year, month, day, hour, minute;
    char strYear[5], strMonth[3], strDay[3], strHour[3], strMinute[3];
    strncpy(strDay, date, 2);
    strncpy(strMonth, date + 3, 2);
    strncpy(strYear, date + 6, 4);
    strncpy(strDay, date, 2);
    strncpy(strMonth, date + 3, 2);

}