int* multiplyMatrice(int* tab1, int* tab2){
    if(tab1.length==tab2[0].length){
        int dim1x = tab1.length;
        int dim1y = tab1[0].length;
        int dim2x = tab1.length;
        int dim2y = tab1[0].length;
        int mul[dimx][dimy];
        for(int i = 0; i < dim1x; i++)
        {
            for(int j = 0; j < dim2y; j++)
            {
                mul[i][j]=0;
                for(int k = 0; k < dim1y; k++)
                {
                    mul[i][j] += tab1[i][k] * tab2[k][j];
                }
            }
        }
    }
    return mul;
}