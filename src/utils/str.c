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