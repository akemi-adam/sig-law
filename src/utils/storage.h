#ifndef STORAGE
#define STORAGE

#include <stdbool.h>
#include <stdlib.h>

bool saveFile(const void*, const size_t, int, const char*);

bool readFile(void*, const size_t, int, const char*);



#endif