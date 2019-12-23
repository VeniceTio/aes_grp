#include "aes.h"
#include "utils.h"
#include "keyExtention.h"

int main(int argc, char* argv[]) {
    //test print matrice
    uint8_t tab[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    print(tab);
    printf("\n\n\n");
    print(shiftRows(tab));

    char hex[256];

    stringToHexStr("Thank you", &hex);

    long num = strtol(hex, NULL, 16);

    printf("hex is %s.\n", hex);
    printf("hex length %i.\n", strlen(hex));

    printf("Hex in numerical: %ld \n", num);
    printf("Hex in Hex: %#010x\n", num);

    struct HexDigits digits;
    digits = getHexDigits(183);
    printf("Digit 1: %i\n", digits.d1);
    printf("Digit 2: %i\n", digits.d2);

    uint8_t key[KEY_LENGTH / 8];
    hexStrToKey(hex, &key);



  return 0;
}

