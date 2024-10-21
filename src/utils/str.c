#include <stdbool.h>

/**
 * Verifica se um caracter é acentuado
 * 
 * @param const char c: caractér a ser avaliado
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isAccentedChar(const char c) {
    char accents[] = "áéíóúàèìòùâêîôûãõäëïöüçÁÉÍÓÚÀÈÌÒÙÂÊÎÔÛÃÕÄËÏÖÜÇ";
    for (int i = 0; accents[i] != '\0'; i++) {
        if (c == accents[i]) return true;
    }
    return false;
}

/**
 * Conta todos os acentos de uma string
 * 
 * @param const char* str: String a ser avaliada
 * 
 * @return int
 * 
 * Authors:
 *  - ChatGPT
 */
int countAccents(const char* str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isAccentedChar(str[i])) count++;
    }
    return count;
}