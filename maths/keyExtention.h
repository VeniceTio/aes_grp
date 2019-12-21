#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern int KEY_LENGTH;

char* stringToHexStr(char* text, char output[256]);
void hexStrToKey(char* hex, int* key);
