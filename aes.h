#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

void subWord(uint8_t word[4]);

uint8_t* subBytes(uint8_t* word);
uint8_t subByte(uint8_t val);

uint8_t* invSubBytes(uint8_t* word);
uint8_t invSubByte(uint8_t val);

void addRoundKey(uint8_t* state, uint8_t key[4][4]);

uint8_t* shiftRows(uint8_t* word);
uint8_t* mixColumns(uint8_t* word);

uint8_t* invShiftRows(uint8_t* word);
uint8_t* invMixColumns(uint8_t* word);
uint8_t* multiply(uint8_t* column);
uint8_t* invMultiply(uint8_t* column);
uint8_t* getColumn(uint8_t* matrice, int pos);

#ifndef GLOBALVAR_AES
#define GLOBALVAR_AES

extern int KEY_LENGTH;
extern int NB_ROUNDS;

uint8_t sbox[256];

extern const uint8_t inv_sbox[256];

extern const uint8_t matriceMix[16];

extern const uint8_t inv_matriceMix[16];

#endif
