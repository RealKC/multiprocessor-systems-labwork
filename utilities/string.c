#include "utilities.h"

// Adapted from "The C Programming language", 2nd ed., p 104, Kernighan and Ritchie
int mystrcmp(u8 const* s, u8 const* t)
{
    for (; *s == *t; s++, t++) {
        if (*s == '\0') {
            return 0;
        }
    }

    return *s - *t;
}

// Adapted from "The C Programming language", 2nd ed., p 103, Kernighan and Ritchie
int mystrlen(u8 const* s)
{
    u8 const* p = s;

    while (*p != '\0') {
        p++;
    }

    return p - s;
}
