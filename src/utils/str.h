#ifndef STR
#define STR

#include <stdbool.h>

bool isAccentedChar(const char);
bool isStartOfUtf8Char(unsigned char);
int countAccents(const char*);

#endif