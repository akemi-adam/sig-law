#ifndef VALIDATION
#define VALIDATION

#include <stdbool.h>

bool isString(const char*);

bool isEmpty(const char*);

bool isPositive(int);

bool isEmail(char[55]);

bool isTelephone(const char[14]);

bool isCpfValid(char[12]);

bool isCpf(char[12]);

bool isCna(char[13]);

bool isLeapYear(int);

int maxDaysInMonth(int, int);

bool isDay(int, int, int);

bool isMonth(int);

bool isYear(int);

bool isDate(char[11]);

#endif