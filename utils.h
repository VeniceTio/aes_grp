#include <stdint.h>
#include <stddef.h>

struct HexDigits {
    int d1;
    int d2;
};

//P est un polynome

uint8_t* xorWords(uint8_t* word1, uint8_t* word2);
void printWord(uint8_t* word);
void printWordHex(uint8_t* word);
void print(uint8_t* display);//affiche un tableau de 16 uint8_t
struct HexDigits getHexDigits(uint8_t byte);
uint8_t shiftMonome(uint8_t monome); // réalise un shift de 1 sur un monome
uint8_t shiftPolynome(uint8_t polynome); // Réalise la multiplication a*(P)
uint8_t shiftNPolynome(int k, uint8_t polynome); // Réalisea^k(P)
uint8_t multiplication(uint8_t o1, uint8_t o2); // multipli 2 uint8_t entre eux

void print(uint8_t* display);
