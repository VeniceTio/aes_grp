#include "utils.h"

#include <stdio.h>

void print(uint8_t* display){
    for(size_t i = 0; i < 16; i+=4)
    {
        printf("[%c, %c, %c, %c]\n", display[i], display[i+1], display[i+2], display[i+3]);
    }
}

int length(uint8_t* array) {
    return (sizeof(array) / sizeof(array[0]));
}

int length2(uint8_t** array) {
    return (sizeof(array) / sizeof(array[0]));
}

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
