#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

//***********************************************************
//Un overload de print pour afficher les uint de facon plus graphique
void print(uint8_t* display){
    for(size_t i = 0; i < 16; i+=4)
    {
        printf("[%c, %c, %c, %c]\n", display[i], display[i+1], display[i+2], display[i+3]);
    }
}

uint8_t* multiplyMatrice(uint8_t* tab1,int dim1x,int dim1y,const uint8_t* tab2,int dim2x,int dim2y){
    uint8_t* mul = NULL;
    if(dim1x == dim2y) {
        uint8_t *mul = malloc(sizeof(uint8_t) * 4);
        for (int i = 0; i < dim1x; i++) {
            for (int j = 0; j < dim1y; j++) {
                mul[i + j] = 0;
                for (int k = 0; k < dim1y; k++) {
                    mul[i + j] += tab1[i + k] * tab2[k + j];
                    printf("%d = %d * %d\n", mul[i + j],tab1[i + k],tab2[k + j]);
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
uint8_t* multiplyMatrice(uint8_t* tab1,int dim1x,int dim1y,const uint8_t* tab2,int dim2x,int dim2y){
    uint8_t* mul = NULL;
    if(dim1x == dim2y) {
        uint8_t *mul = malloc(sizeof(uint8_t) * 4);
        for (int i = 0; i < dim1x; i++) {
            for (int j = 0; j < dim1y; j++) {
                mul[i + j] = 0;
                for (int k = 0; k < dim1y; k++) {
                    mul[i + j] += tab1[i + k] * tab2[k + j];
                    printf("%d = %d * %d\n", mul[i + j],tab1[i + k],tab2[k + j]);
                }
            }

        }
    }
    return mul;
}
