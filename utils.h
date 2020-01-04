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
uint8_t multiplication(uint8_t o1, uint8_t o2);
struct HexDigits getHexDigits(uint8_t byte);
