#include <stdint.h>
#include <stddef.h>

struct HexDigits {
    int d1;
    int d2;
};

uint8_t* xorWords(uint8_t* word1, uint8_t* word2);
void printWord(uint8_t* word);
void printWordHex(uint8_t* word);
void printVer(uint8_t* display);
void print(uint8_t* display);
uint8_t multiplication(uint8_t o1, uint8_t o2);
struct HexDigits getHexDigits(uint8_t byte);
uint8_t shiftMonome(uint8_t monome);
uint8_t shiftPolynome(uint8_t polynome);
uint8_t shiftNPolynome(int k, uint8_t polynome);
