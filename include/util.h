#ifndef UTIL_H__
#define UTIL_H__

#include <stdio.h>

void die(const char* msg);

void erase_last_two_chars(FILE* f);

long GetTickCount();

#endif /* UTIL_H */
