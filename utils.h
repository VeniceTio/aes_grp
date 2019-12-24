#include <stdint.h>
#include <stddef.h>

struct HexDigits {
    int d1;
    int d2;
};

void print(uint8_t* display);
int** multiplyMatrice(int tab1[4][4], int tab2[4][4]);
int length(uint8_t* array);
int length2(uint8_t** array);
struct HexDigits getHexDigits(uint8_t byte);

void print(uint8_t* display);
uint8_t* multiplyMatrice(uint8_t* tab1,int dim1x,int dim1y, const uint8_t* tab2,int dim2x,int dim2y);
