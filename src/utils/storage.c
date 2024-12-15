#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./storage.h"

/**
 * Salva um conteúdo em um arquivo
 * 
 * @param const void *ptr: Conteúdo a ser salvo
 * @param const size_t size: Tamanho do tipo do conteúdo
 * @param int elementsNumber: Número de elementos
 * @param const char *filename: Caminho completo do arquivo
 * 
 * @return bool: Retorna false se houver alguma falha ao salvar o arquivo, true se salvar com sucesso
 */
bool saveFile(const void *ptr, const size_t size, int elementsNumber, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) return false;
    // size_t written = fwrite(ptr, size, sizeof(ptr), fp);
    fwrite(ptr, size, elementsNumber, fp);
    fclose(fp);
    return true;
}

/**
 * Ler o conteúdo de um arquivo
 * 
 * @param void *ptr: Destino da leitura do arquivo
 * @param const size_t: Tamanho do tipo do conteúdo
 * @param int elementsNumber: Número de elementos
 * @param const char *filename: Nome do arquivo
 * 
 * @return bool: False se houver alguma falha na leitura do arquivo, true se ler com sucesso
 */
bool readFile(void *ptr, const size_t size, int elementsNumber, const char *filename) {
    FILE *fp;
    fp = fopen(filename, "rb");
    if (fp == NULL) return false;
    fread(ptr, size, elementsNumber, fp);
    fclose(fp);
    return true;
}

/**
 * Retorna o número de elementos em um arquivo binário.
 * 
 * @param const char *filename: Caminho completo do arquivo
 * @param const size_t structSize: Tamanho da struct armazenada
 * 
 * @return int: Número de elementos no arquivo, 0 se o arquivo não existir ou -1 em caso de erro
 * 
 * Authors:
 *  - ChatGPT
 */
int getNumberOfElements(const char *filename, const size_t structSize) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) return 0; // Retorna 0 se o arquivo não existir

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fclose(fp);

    if (fileSize < 0) return -1;

    return fileSize / structSize;
}

