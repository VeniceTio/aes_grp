#include "aes.h"
#include "utils.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    //test print matrice
    uint8_t tab[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    print(tab);
    printf("\n\n\n");

    uint8_t* tab_shift = shiftRows(tab);

    print(tab_shift);
    printf("\n\n\n");

    uint8_t* tab_sub = subBytes(tab_shift);

    print(tab_sub);
    printf("\n\n\n");

    uint8_t* tab_inv_sub = invSubBytes(tab_sub);

    print(tab_inv_sub);
    printf("\n\n\n");
  return 0;
}
