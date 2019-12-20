#include "aes.h"
#include "utils.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    //test print matrice
    uint8_t tab[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    print(tab);
    printf("\n\n\n");
    print(shiftRows(tab));
  return 0;
}
