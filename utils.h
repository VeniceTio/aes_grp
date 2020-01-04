#include <stdint.h>
#include <stddef.h>

struct HexDigits {
    int d1;
    int d2;
};

uint8_t* xorWords(uint8_t* word1, uint8_t* word2);
void printWord(uint8_t* word);
void printWordHex(uint8_t* word);
void print(uint8_t* display);
int** multiplyMatrice(int tab1[4][4], int tab2[4][4]);
struct HexDigits getHexDigits(uint8_t byte);
