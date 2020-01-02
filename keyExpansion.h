#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "aes.h"

uint8_t* getRConWord(int i);
void strToKeyByte(char* text, uint8_t output[16]);
void keyExpansion(uint8_t key[KEY_LENGTH / 8], uint8_t** extKeyW);
void rotWord(uint8_t* word);
char* stringToHexStr(char* text, char output[256]);
void hexStrToKey(char* hex, uint8_t* key);
