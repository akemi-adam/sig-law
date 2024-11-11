#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


/**
 * Função auxiliar para verificar se um byte é parte de um caractere UTF-8. Verifica se não é um byte de continuação.
 * 
 * @param unsigned char byte
 * 
 * @return bool
 * 
 * Authors:
 *  - ChatGPT
 */
bool isStartOfUtf8Char(unsigned char byte) {
    return (byte & 0xC0) != 0x80;
}

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
 * Função que conta acentos em uma string, lidando com UTF-8.
 * 
 * @param const char* str
 * 
 * @return int
 * 
 * Authors:
 *  - ChatGPT
 */
int countAccents(const char* str) {
    int count = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        unsigned char currentByte = str[i];

        // Se o byte atual é o início de um caractere UTF-8
        if (isStartOfUtf8Char(currentByte)) {
            // Avança para verificar o caractere completo
            if (isAccentedChar(currentByte)) {
                count++;
            }

            // Verifica se é um caractere de 2 ou 3 bytes
            if ((currentByte & 0xE0) == 0xC0) { // Caractere de 2 bytes
                i += 2; // Avança 2 bytes
            } else if ((currentByte & 0xF0) == 0xE0) { // Caractere de 3 bytes
                i += 3; // Avança 3 bytes
            } else {
                i++; // Caso inesperado, apenas avança 1 byte
            }
        } else {
            // Se é um byte de continuação, apenas avança
            i++;
        }
    }
    
    return count;
}


/**
 * Converte uma String para int
 * 
 * @param char *str: String a ser convertida
 * @param int *result: Endereço para atribuir o valor da conversão
 * 
 * @return bool: Status da conversão
 * 
 * Authors:
 *  - ChatGPT
 */
bool parseInt(const char *str, int *result) {
    if (str == NULL || *str == '\0') return false;

    char *endptr;
    errno = 0;
    long value = strtol(str, &endptr, 10);
    
    if (endptr == str || errno != 0 || *endptr != '\0') return false;

    *result = (int) value;
    return true;
}

/**
 * Converte uma String para double
 * 
 * @param char *str: String a ser convertida
 * @param double *result: Endereço para atribuir o valor da conversão
 * 
 * @return bool: Resultado da conversão
 * 
 * Authors:
 *  - ChatGPT
 */
bool parseDouble(const char *str, double *result) {
    if (str == NULL || *str == '\0') return false;

    char *endptr;
    errno = 0;
    double val = strtod(str, &endptr);

    if (errno != 0 || endptr == str || *endptr != '\0') return false;

    *result = val;
    return true;
}

/**
 * Verifica se há espaços em branco no início ou no final da string
 * 
 * @param const char str*
 * 
 * @return bool
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 * 
 */
bool hasInvalidSpaces(const char *str) {
    int end = (int) strlen(str) - 1;
    return str[0] == ' ' || str[end] == ' ';
}