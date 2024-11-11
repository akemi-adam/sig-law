#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "./str.h"
#include "./validation.h"

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
    if (str == NULL || str[0] == '\0' || hasInvalidSpaces(str)) return false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!(isalpha(str[i]) || str[i] == ' ' || isAccentedChar(str[i]))) return false;
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
 * Verifica se a string não é vazia
 * 
 * @param const char *str
 * 
 * @return bool
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
bool isRequired(const char *str) {
    return !isEmpty(str);
}

/**
 * Alias para a função isdigit
 * 
 * @param const char *str
 * 
 * @return bool
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
bool isNumber(const char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
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
 * @param char *email
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isEmail(const char *email) {
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
 * @param char *tel
 * 
 * @return bool
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
bool isTelephone(const char *tel) {
    int telDefaultSize = 13;
    int telSize = (int) strlen(tel);
    if (telSize != telDefaultSize || !isdigit(tel[0]) || !isdigit(tel[1]) || tel[2] != ' ' || tel[3] != '9' || tel[8] != '-') {
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
        if (strcmp(ddd, validDDDs[i])) {
            hasDDD = true;
            break;
        }
    }

    if (!hasDDD) return false;
    
    for (int i = 4; i < telDefaultSize; i++) {
        if (i == 8) continue;
        if (!isdigit(tel[i])) return false;
    }

    return true;
}

/**
 * Verifica a validade do CPF
 * 
 * @param char *cpf
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isCpfValid(const char *cpf) {
    int sum = 0, remainder;

    for (int i = 0; i < 9; i++) sum += (cpf[i] - '0') * (10 - i);
    remainder = (sum * 10) % 11;
    if (remainder == 10) remainder = 0;
    if (remainder != (cpf[9] - '0')) return false;

    sum = 0;
    for (int i = 0; i < 10; i++) sum += (cpf[i] - '0') * (11 - i);
    remainder = (sum * 10) % 11;
    if (remainder == 10) remainder = 0;
    
    return remainder == (cpf[10] - '0');
}


/**
 * Verifica se o tamanho do CPF é válido e se é formado apenas por dígitos. Depois, faz o cálculo de verificação do CPF
 * 
 * @param char *cpf
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isCpf(const char *cpf) {
    if (strlen(cpf) != 11) return false;
    for (int i = 0; i < 11; i++) if (!isdigit(cpf[i])) return false;
    return isCpfValid(cpf);
}


/**
 * Verifica se o CNA tem o tamanho válido e se é composto apenas por números
 * 
 * @param const char *cna
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isCna(const char *cna) {
    int cnaLength = strlen(cna);
    if (cnaLength > 12 || isEmpty(cna)) return false;
    for (int i = 0; i < cnaLength; i++) {
        if (!isdigit(cna[i])) return false;
    }
    return true;
}

/**
 * Verifica se o ano é bissexto
 * 
 * @param int year
 * 
 * Authors:
 *  - ChatGPT
 */
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * Retorna o número máximo de dias em um mês específico
 * 
 * @param int month: mês
 * @param int year: ano
 * 
 * @return int
 * 
 * Authors:
 *  - ChatGPT
 */
int maxDaysInMonth(int month, int year) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && isLeapYear(year)) return 29;

    return month >= 1 && month <= 12
        ? daysInMonth[month - 1]
        : 0;
}

/**
 * Verifica se o dia é válido
 * 
 * @param int day
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isDay(int day, int month, int year) {
    int maxDays = maxDaysInMonth(month, year);
    if (!maxDays) return false;
    return day >= 1 && day <= maxDays;
}

/**
 * Verifica se o mês é válido
 * 
 * @param int month
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isMonth(int month) {
    return month >= 1 && month <= 12;
}

/**
 * Verifica se o ano é maior que zero
 * 
 * @param int year
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isYear(int year) {
    return year > 0;
}

/**
 * Verifica se a data está no formato DD/MM/YYYY
 * 
 * @param const char *dateStr
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isDate(const char *dateStr) {
    int day, month, year;
    char dayStr[3], monthStr[3], yearStr[5];

    if (strlen(dateStr) != 10 || dateStr[2] != '/' || dateStr[5] != '/') return false;

    strncpy(dayStr, dateStr, 2);
    dayStr[2] = '\0';
    strncpy(monthStr, dateStr + 3, 2);
    monthStr[2] = '\0';
    strncpy(yearStr, dateStr + 6, 4);
    yearStr[4] = '\0';

    if (!parseInt(dayStr, &day) || !parseInt(monthStr, &month) || !parseInt(yearStr, &year)) return false;

    return isDay(day, month, year) && isMonth(month) && isYear(year);
}

int validateString(const char *str) {
    return isString(str) ? NO_VALIDATION_ERROR : IS_STRING_ERROR;
}

int validateRequired(const char *str) {
    return isRequired(str) ? NO_VALIDATION_ERROR : IS_REQUIRED_ERROR;
}

int validateEmail(const char *email) {
    return isEmail(email) ? NO_VALIDATION_ERROR : IS_EMAIL_ERROR;
}

int validateTelephone(const char *tel) {
    return isTelephone(tel) ? NO_VALIDATION_ERROR : IS_TELEPHONE_ERROR;
}

int validateCpf(const char *cpf) {
    return isCpf(cpf) ? NO_VALIDATION_ERROR : IS_CPF_ERROR;
}

int validateCna(const char *cna) {
    return isCna(cna) ? NO_VALIDATION_ERROR : IS_CNA_ERROR;
}

int validateDate(const char *dateStr) {
    return isDate(dateStr) ? NO_VALIDATION_ERROR : IS_DATE_ERROR;
}

int validatePositive(const char *strNumber) {
    int number = 123;
    if (!parseInt(strNumber, &number)) return IS_POSITIVE_ERROR;
    return isPositive(number) ? NO_VALIDATION_ERROR : IS_POSITIVE_ERROR;
}

int validateNumber(const char *number) {
    return isNumber(number) ? NO_VALIDATION_ERROR : IS_NUMBER_ERROR;
}