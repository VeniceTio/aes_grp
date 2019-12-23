#include "utils.h"

#include <stdio.h>

void print(uint8_t* display){
    for(size_t i = 0; i < 16; i+=4)
    {
        printf("[%c, %c, %c, %c]\n", display[i], display[i+1], display[i+2], display[i+3]);
    }
}

uint8_t* multiplyMatrice(uint8_t* tab1,int dim1x,int dim1y, uint8_t* tab2,int dim2x,int dim2y){
    uint8_t* mul = NULL;
    if(dim1x == dim2y) {
        //int dim1x = tab1.length;
        //int dim1y = tab1[0].length;
        uint8_t *mul = malloc(sizeof(uint8_t) * dim1x);
//        for(int i = 0; i < dim1x; i++)
//        {
//            for(int j = 0; j < dim2y; j++)
//            {
//                mul[i+j]=0;
//                for(int k = 0; k < dim1y; k++)
//                {
//                    mul[i] += tab1[i+k] * tab2[k+j];
//                    //[i][j]
//                }
//            }
//        }
        for (int i = 0; i < dim1x; i++) {
            for (int j = 0; j < dim1y; j++) {
                mul[i + j] = 0;
                for (int k = 0; k < dim1y; k++) {
                    mul[i + j] += atoi(tab1[i + k]) * tab2[k + j];
                    printf("%d\n", mul[i + j]);
                }
            }

        }
    }
    return mul;
}
