#include <stdio.h>
#include <stdbool.h>
#include "./storage.h"

/**
 * Salva um conteúdo em um arquivo
 * 
 * @param const void *ptr: Conteúdo a ser salvo
 * @param const size_t size: Tamanho do tipo do conteúdo
 * @param const char *filename: Caminho completo do arquivo
 * 
 * @return bool: Retorna false se houver alguma falha ao salvar o arquivo, true se salvar com sucesso
 */
bool saveFile(const void *ptr, const size_t size, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) return false;
    // size_t written = fwrite(ptr, size, sizeof(ptr), fp);
    size_t written = fwrite(ptr, size, 1, fp);
    fclose(fp);
    return true;
}

