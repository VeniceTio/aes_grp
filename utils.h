#include <stdint.h>

struct HexDigits {
    int d1;
    int d2;
};

void print(uint8_t* display);
int** multiplyMatrice(int tab1[4][4], int tab2[4][4]);
int length(uint8_t* array);
int length2(uint8_t** array);
struct HexDigits getHexDigits(uint8_t byte);
