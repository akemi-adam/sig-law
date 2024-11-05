#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "./str.h"

/**
 * Verifica se a string conter apenas caracteres alpha
 * 
 * @param char *str
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isString(const char *str) {
    if (str == NULL || str[0] == '\0') return false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) return false;
    }
    return true;
}

/**
 * Verifica se a string é vazia
 * 
 * @param const char *str
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isEmpty(const char *str) {
    return str[0] == '\0';
}

/**
 * Verifica se o número é positivo
 * 
 * @param int number
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isPositive(int number) {
    return number >= 0;
}

/**
 * Verifica se o e-mail é válido
 * 
 * @param char email[55]
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isEmail(char email[55]) {
    int atPos = -1, dotPos = -1, len = strlen(email);
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') atPos = i;
        if (email[i] == '.') dotPos = i;
    }
    return atPos > 0 && dotPos > atPos + 1 && dotPos < len - 1;
}

/**
 * Verifica se o telefone é válido no formato XX 9XXXX-XXXX
 * 
 * @param char tel[14]
 * 
 * @return bool
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
bool isTelephone(const char tel[14]) {
    if (strlen(tel) != 13 || !isdigit(tel[0]) || !isdigit(tel[1]) || tel[2] != ' ' || tel[3] != '9' || tel[8] != '-') {
        return false;
    }

    const char* validDDDs[] = {
        "61", "62", "64", "65", "66", "67", "82", "71", "73",
        "74", "75", "77", "85", "88", "98", "99", "83", "81",
        "87", "86", "89", "84", "79", "68", "96", "92", "97",
        "91", "93", "94", "69", "95", "63", "27", "28", "31",
        "32", "33", "34", "35", "37", "38", "21", "22", "24",
        "11", "12", "13", "14", "15", "16", "17", "18", "19",
        "41", "42", "43", "44", "45", "46", "49", "51", "53",
        "54", "55", "47", "48"
    };

    bool hasDDD = false;
    char ddd[3];
    strncpy(ddd, tel, 2);

    for (int i = 0; i < 67; i++) {
        if (strcmp(ddd, validDDDs)) {
            hasDDD = true;
            break;
        }
    }

    if (!hasDDD) return false;
    
    for (int i = 4; i < strlen(tel); i++) {
        if (i == 8) continue;
        if (!isdigit(tel[i])) return false;
    }

    return true;
}


