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

/**
 * Verifica a validade do CPF
 * 
 * @param char cpf[12]
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isCpfValid(char cpf[12]) {
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
 * @param char cpf[12]
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isCpf(char cpf[12]) {
    if (strlen(cpf) != 11) return false;
    for (int i = 0; i < 11; i++) if (!isdigit(cpf[i])) return false;
    return isCpfValid(cpf);
}


/**
 * Verifica se o CNA tem o tamanho válido e se é composto apenas por números
 * 
 * @param char cna[13]
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isCna(char cna[13]) {
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

