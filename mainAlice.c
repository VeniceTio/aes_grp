#include "aes.h"
#include "utils.h"
#include "keyExpansion.h"
#include "file.h"

#include <stdio.h>

int main(int argc, char const *argv[]) {

  uint8_t* text = getTextFromFile("alice.txt");
  printf("%s\n", text);

  int size = fileSize("alice.txt");
  printf("%d\n", size);

  uint8_t in[16], out[16];
  FILE* file = fopen("aliceDecipher.txt", "a");

  uint8_t extKey[NB_ROUNDS+1][4];
  uint8_t key[16] =  {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
  keyExpansion(key, (uint8_t**)extKey);

  for (int i = 0; i < size; i++) {
    if(i % 16 == 0 && i != 0){
      invCipher(in, out, (uint8_t**)extKey);

      fwrite(out, 16, sizeof(out), file);
    }

    in[i % 16] = text[i];
  }

  return 0;
}
