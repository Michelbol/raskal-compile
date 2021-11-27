#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

typedef char *String;

String string(String);
String concatStringInt(char *word, int numero);
String concatIntString(int numero, char *word);

#endif