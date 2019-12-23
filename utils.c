#include "utils.h"

#include <stdio.h>

//***********************************************************
//Un overload de print pour afficher les uint de facon plus graphique
void print(uint8_t* display){
    for(size_t i = 0; i < 16; i+=4)
    {
        printf("[%c, %c, %c, %c]\n", display[i], display[i+1], display[i+2], display[i+3]);
    }
}

//Longueur d'un array de uint8
int length(uint8_t* array) {
    return (sizeof(array) / sizeof(array[0]));
}

int length2(uint8_t** array) {
    return (sizeof(array) / sizeof(array[0]));
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
int** multiplyMatrice(int tab1[4][4], int tab2[4][4]){
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
    }
    return NULL;
}
