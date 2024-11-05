#ifndef STR
#define STR

#include <stdbool.h>

bool isAccentedChar(const char);
bool isStartOfUtf8Char(unsigned char);
int countAccents(const char*);
bool parseInt(const char*, int*);
bool parseDouble(const char*, double*);

#endif