int[][] multiplyMatrice(int[][] tab1, int[][] tab2){
    if(tab1.length == tab2.length && tab1[0].length == tab2[0].length){
        int dimx = tab1.length;
        int dimy = tab1[0].length;
        int[dimx][dimy] mul;
        for(int i = 0; i < dimx; i++)
        {
            for(int j = 0; j < dimy; j++)
            {
                mul[i][j]=0;
                for(k = 0; k < dimy; k++)
                {
                    mul[i][j] += tab1[i][k] * tab2[k][j];
                }
            }
        }
    }
    return mul;
}