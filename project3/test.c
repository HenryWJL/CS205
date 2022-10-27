#include <stdio.h>
#include "header.h"

int main()
{
    struct Matrix matrix=createMatrix("[[1.2,-2.5,-3],[2.7,-4,6.5],[3.1,5.2,7.9]]");
    struct Matrix matrix1=createZeros(2,3);
    struct Matrix matrix2=createOnes(3,3);
    struct Matrix matrix3=createRand(1,3,9);
    displayMatrix(matrix);
    displayMatrix(matrix1);
    displayMatrix(matrix2);
    displayMatrix(matrix3);
    deleteMatrix(&matrix2);
    copyMatrix(&matrix1,matrix3);
    displayMatrix(matrix1);
    displayMatrix(matrix2);
    struct Matrix matrix4=multiplyMatrix(matrix1,matrix);
    reshapeMatrix(&matrix1,3,1);
    displayMatrix(matrix4);
    displayMatrix(matrix1);

    matrix=createMatrix("[[1.2,-2.5,-3],[2.7,-4,6.5],[3.1,5.2,7.9]]");
    matrix1=createZeros(2,3);
    matrix2=createOnes(3,3);
    struct Matrix matrix5=subtractMatrix(matrix,matrix2);
    struct Matrix matrix6=addScalar(matrix1,5.2);
    struct Matrix matrix7=multiplyScalar(matrix6,6.7);
    displayMatrix(matrix5);
    displayMatrix(matrix6);
    displayMatrix(matrix7);
    printf("%.2f\n",max(matrix5));
    printf("%.2f\n",min(matrix6));
    printf("%.2f\n",mean(matrix7));
}


