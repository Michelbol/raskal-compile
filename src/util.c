/*
 * util.c - commonly used utility functions.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

char *string(char *s) {
    char *p = (char *)malloc(strlen(s)+1);
    strcpy(p, s);
    return p;
}
