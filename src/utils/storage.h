#ifndef STORAGE
#define STORAGE

#include <stdbool.h>

bool saveFile(const void*, const size_t, const char*);

bool readFile(void*, const size_t, const char*);

#endif