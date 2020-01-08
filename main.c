#include "aes.h"
#include "utils.h"
#include "keyExpansion.h"
#include "file.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    // Test print matrice
    uint8_t tab[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    print(tab);
    printf("\n\n\n");

	// Test Shift Rows
    uint8_t* tab_shift = shift_rows(tab);

    print(tab_shift);
    printf("\n\n\n");

	// Test Sub Bytes
    uint8_t* tab_sub = sub_bytes(tab_shift);

    print(tab_sub);
    printf("\n\n\n");

	// Test Inv Sub Bytes
    uint8_t* tab_inv_sub = inv_sub_bytes(tab_sub);

    print(tab_inv_sub);

    // Test multiply
    uint8_t* tab_multiply = multiply(tab);
    printf("\nmultiply :\n");
    print(tab_multiply);
    printf("\ninv_multiply :\n");
    print(inv_multiply(tab_multiply));

    printf("\n\nmix_columns\n");
    print(mix_columns(tab));
    printf("\n\ninv_mix_columns\n");
    print(inv_mix_columns(mix_columns(tab)));
    printf("\n");
    printf("mix_columns(shift_rows)\n");
    print(mix_columns(shift_rows(tab)));
    printf("inv_shift_rows(invMixColumn(mix_columns(shift_rows)))\n");
    print(inv_shift_rows(inv_mix_columns(mix_columns(shift_rows(tab)))));


  // Test inv_shift_rows
    uint8_t* tab_origin = inv_shift_rows(tab_inv_sub);
    printf("inv_shift_rows\n");
    print(tab_origin);
    printf("\n\n\n");

    // Test mix_columns
    uint8_t* tab_columns_mix = mix_columns(tab_origin);

    print(tab_columns_mix);
    printf("\n\n\n");

    // Test inv_mix_columns
    uint8_t* tab_columns_unmix = inv_mix_columns(tab_columns_mix);

    print(tab_columns_unmix);
    printf("\n\n\n");

	// Test Hexadecimal
    char hex[256];

    char* phrase = "Thank you";

    stringToHexStr(phrase, hex);

    printf("Keygen Phrase: %s\n", phrase);
    printf("Text In Hex %s.\n", hex);
    printf("Length of Hex String %li.\n", strlen(hex));

    long num = strtol(hex, NULL, 16);
    printf("Hex in numerical: %ld \n", num);

    struct HexDigits digits;
    digits = getHexDigits(183);
    printf("Digit 1: %i\n", digits.d1);
    printf("Digit 2: %i\n", digits.d2);

    //***********************************
	// Test Extention Clefs

	// Creer la clef en bits a partir de la phrase
    uint8_t key[(KEY_LENGTH / 8)];
    strToKeyByte(phrase, key);

    // Afficher les bytes de la clef
    printf("Key Bytes:");
    for(int i = 0; i < (KEY_LENGTH / 8); ++i) {
        printf("%i ", key[i]);
    }

    // Allocation memoire de 4 Mots Binaires de 4 uint8_t (byte) chacun
    uint8_t extKey[(NB_ROUNDS+1) * 4][4];

    uint8_t testKey[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

    // Etendre la clef en (NbRound + 1) clefs
    keyExpansion(testKey, (uint8_t**)extKey);

    /*for(int i = 0; i < (KEY_LENGTH / 32) * (NB_ROUNDS+1); ++i) {
        if(i % 4 == 0)
            printf("\n Key:\n");
        printWordHex(&extKey[i]);
    }*/

  uint8_t input[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
  uint8_t output[16];
  uint8_t decipher[16];

  cipher(input, output, (uint8_t**)extKey);

  printf("\nOutput \n");
  print(output);

  printf("%s\n", get_text_from_file("test.txt"));
  printf("%d\n", file_size("test.txt"));

  printf("\n------------------INVERSE CIPHER DECIPHER-----------------------\n");
  inv_cipher(output, decipher, (uint8_t**)extKey);
  printf("\nINPUT\n");
  printVer(input);

  return 0;
}
