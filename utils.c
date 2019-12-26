#include "utils.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

//***********************************************************
// Applique le OU exclusif entre 2 Mots de 4 Bytes
uint8_t* xorWords(uint8_t* word1, uint8_t* word2) {
    static uint8_t* res;
    res = malloc(sizeof(uint8_t) * 4);

    res[0] = word1[0] ^ word2[0];
    res[1] = word1[1] ^ word2[1];
    res[2] = word1[2] ^ word2[2];
    res[3] = word1[3] ^ word2[3];

    return res;
}

//***********************************************************
//Un overload de print pour afficher un Mot de 4 Bytes en Hexadicimal
void printWordHex(uint8_t* word) {
    printf("[%x, %x, %x, %x]\n", word[0] & 0xff, word[1] & 0xff, word[2] & 0xff, word[3] & 0xff);
}

//***********************************************************
//Un overload de print pour afficher un Mot de 4 Bytes
void printWord(uint8_t* word) {
    printf("[%i, %i, %i, %i]\n", word[0], word[1], word[2], word[3]);
}

//***********************************************************
//Un overload de print pour afficher les uint de facon plus graphique
void print(uint8_t* display){
    for(size_t i = 0; i < 16; i+=4)
    {
        printf("[%c, %c, %c, %c]\n", display[i], display[i+1], display[i+2], display[i+3]);
    }
}

//***********************************************************
//Extrait les 2 chiffres du bit en representation Hexadecimale
struct HexDigits getHexDigits(uint8_t byte) {
    struct HexDigits digits;
    //Extrait le premier chiffre
    digits.d1 = (int)floor(byte / 16);
    //Extrait le deuxieme chiffre
    digits.d2 = byte % 16;

    return digits;
}

//***********************************************************
//Multiplication de deux matrices
/*int** multiplyMatrice(int tab1[4][4], int tab2[4][4]){
    if(length2(tab1) == length(tab2[0])){
        int dim1x = length2(tab1);
        int dim1y = length(tab1[0]);
        int dim2x = length2(tab1);
        int dim2y = length(tab1[0]);
        uint8_t** mul = malloc(sizeof(uint8_t) * dim1x);
        for(int i = 0; i < dim1x; i++)
        {
            for(int j = 0; j < dim2y; j++)
            {
                mul[i][j]=0;
                for(int k = 0; k < dim1y; k++)
                {
                    mul[i] += tab1[i][k] * tab2[k][j];
                    //[i][j]
                }
            }
        }
        return mul;
    }
    else{
      return NULL;
    }

}*/