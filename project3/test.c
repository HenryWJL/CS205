#include <stdio.h>
#include "header.h"

int main()
{
    float a[4]={1,2,3,4};
    float b[4]={4,5,6,7};
    struct Matrix matrix=createMatrix("[a,2,3,4]");
    struct Matrix matrix1=createMatrix("[4,5,6,7]");
    struct Matrix matrix2=addMatrix(matrix,matrix1);
    // createMatrix(&matrix,1,3);
    // createMatrix(&matrix1,1,4);
    // copyMatrix(&matrix1,matrix);
    displayMatrix(matrix);
    displayMatrix(matrix1);
    displayMatrix(matrix2);
    // printf("%f\n",matrix2.content[2]);

    // for(int i=0;i<3;i++){
    //     printf("%f\n",matrix.content[i]);
    // }
}

