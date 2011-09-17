#include "util.h"

#include <time.h> /* -lrt */
#include <stdio.h>
#include <stdlib.h>

long GetTickCount()
{
    static struct timespec ts;

    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
        die("clock_gettime() failed");

    return ts.tv_nsec;
}

void die(const char* msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void erase_last_two_chars(FILE* f)
{
    if (!f)
        die("File pointer uninitialized");

    long curpos = ftell(f);
    if (curpos < 0)
        die("ftell() failed");
    if (curpos < 3)
        die("Invalid file stream position");

    if (fseek(f, curpos - 2, SEEK_SET) < 0)
        die("fseek() failed");
}

