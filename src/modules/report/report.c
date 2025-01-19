#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./../../utils/interfaces.h"
#include "./../../utils/validation.h"
#include "./../../utils/storage.h"
#include "./../../utils/date.h"
#include "./../../utils/str.h"
#include "./report.h"
#include "../client/client.h"
#include "../lawyer/lawyer.h"
#include "../office/office.h"
#include "../appointment/appointment.h"
#include "../person/person.h"

#ifdef __unix__

#include <termios.h>
#include <unistd.h>


/**
 * Relatórios
 * 
 * @return void
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */

void showReportMenu() {
    printf("Menu Relatórios");
}

#endif