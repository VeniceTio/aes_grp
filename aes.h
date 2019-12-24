#include <stdint.h>

extern int KEY_LENGTH;
extern int NB_ROUNDS;

<<<<<<< HEAD
void subWord(uint8_t word[4]);
void keyExpansion();

void addRoundKey();

uint8_t* subBytes(uint8_t* message);

uint8_t subByte(uint8_t val);

uint8_t* invSubBytes(uint8_t* message);

uint8_t invSubByte(uint8_t val);

uint8_t* shiftRows(uint8_t* message);
uint8_t* mixColumns(uint8_t* message);
