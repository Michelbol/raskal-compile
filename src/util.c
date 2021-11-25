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

String concatStringInt(char *word, int numero){
    int size = strlen(word)+9; // max int is 9 size
    char c_comando[size];
    snprintf(c_comando, size, "%s%i", word, numero);
    return string(c_comando);
}
