#include "aes.h"
#include "utils.h"
#include "keyExpansion.h"
#include "file.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <in_File> <out_File>\n", argv[0]);
        return EXIT_FAILURE;
    }

    uint8_t* text = get_text_from_file(argv[1]);
    printf("%s\n", text);

    int sizeFile = file_size(argv[1]);
    printf("%d\n", sizeFile);

    uint8_t in[16];
    uint8_t out[16];

    FILE* file = fopen(argv[2], "a");

    uint8_t** extKey[(NB_ROUNDS+1) * 4][4];
    uint8_t key[16] =  {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    keyExpansion(key, extKey);

    for (size_t i = 0; i < sizeFile; i++) {
        if(i % 16 == 0 && i != 0){
            uint8_t* tab = malloc(16*sizeof(uint8_t));
            cipher(in, out, extKey);

            copyVertical(out,tab);
            fwrite(tab, 16, sizeof(uint8_t), file);
            free(tab);
        }
        in[i % 16] = text[i];
        if (i==sizeFile-1){
            for(size_t j=(i+1)%16;j<16;j++){
                in[j] = 0;
                printf("%d\n",j);
            }
            uint8_t* tab = malloc(16*sizeof(uint8_t));
            cipher(in, out, extKey);

            copyVertical(out,tab);
            fwrite(tab, 16, sizeof(uint8_t), file);
            free(tab);
        }
    }

    uint8_t* cipherText = get_text_from_file(argv[2]);
    printf("%s\n", cipherText);

    //remove("aliceDecipher.txt");
    return 0;
}