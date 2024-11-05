#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>


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