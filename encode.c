#include "aes.h"
#include "utils.h"
#include "keyExpansion.h"
#include "file.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <in_File> <out_File> <cle>\n", argv[0]);
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
    //uint8_t key[16] =  {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    //uint8_t key[16] =  {0xE4, 0x9C, 0x7B, 0xCB, 0x04, 0x05, 0x06, 0x07, 0x21, 0xC3, 0x16, 0x0B, 0x0C, 0x0D, 0x00, 0x00};
    uint8_t key[16];
//    char text2[sizeof(uint8_t)*sizeFile];
//    printf("la\n");
//    memcpy(&text2, &text, sizeof(uint8_t)*sizeFile);
//    printf("%s\n",text2);
    str_to_key_byte(argv[3], key);
//    printf("la");
//    for(int i = 0; i < (KEY_LENGTH / 8); ++i) {
//        printf("%i ", key[i]);
//    }
//    printf("\n");
    key_expansion(key, extKey);
//    printf("Key Bytes:");
//    printf("la");


    for (size_t i = 0; i < sizeFile; i++) {
        if(i % 16 == 0 && i != 0){
            for(int k = 0; k < 16; k++) {
                printf(" %i ,", in[k]);
            }
            printf("\n");
            uint8_t* tab = malloc(16*sizeof(uint8_t));
            cipher(in, out, extKey);

            //copy_vertical(out,tab);
            fwrite(out, 16, sizeof(uint8_t), file);
            free(tab);
        }
        in[i % 16] = text[i];
        if (i==sizeFile-1){
            for(size_t j=(i+1)%16;j<16;j++){
                in[j] = 0;
                printf("%d\n",j);
            }
            for(int k = 0; k < 16; k++) {
                printf(" %i ,", in[k]);
            }
            uint8_t* tab = malloc(16*sizeof(uint8_t));
            cipher(in, out, extKey);

            //copy_vertical(out,tab);
            fwrite(out, 16, sizeof(uint8_t), file);
            free(tab);
        }
    }

    uint8_t* cipherText = get_text_from_file(argv[2]);
    printf("%s\n", cipherText);

    //remove("aliceDecipher.txt");
    return 0;
}