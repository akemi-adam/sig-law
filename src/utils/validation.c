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

