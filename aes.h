#include <stdint.h>

extern int KEY_LENGTH;
extern int NB_ROUNDS;

void subWord(uint8_t word[4]);
void keyExpansion();
void addRoundKey();
void subBytes(int posX, int posY);
uint8_t* shiftRows(uint8_t* message);
uint8_t* mixColumns(uint8_t* message);
