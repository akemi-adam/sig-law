#ifndef VALIDATION
#define VALIDATION

#include <stdbool.h>

bool isString(const char*);

bool isEmpty(const char*);

bool isPositive(int);

bool isEmail(const char*);

bool isTelephone(const char*);

bool isCpfValid(const char*);

bool isCpf(const char*);

bool isCna(const char*);

bool isLeapYear(int);

int maxDaysInMonth(int, int);

bool isDay(int, int, int);

bool isMonth(int);

bool isYear(int);

bool isDate(const char*);

#endif