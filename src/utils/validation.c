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

