#include <stdio.h>
#include <time.h>
#include "header.h"

int main()
{
    clock_t time_start,time_end;
    struct Matrix matrix1=createOnes(8000,8000);
    struct Matrix matrix2=createOnes(8000,8000);
    time_start=clock();
    struct Matrix matrix4=matmul_improved_3(matrix1,matrix2);
    time_end=clock();
    printf("%f\n",(double)(time_end-time_start)/CLOCKS_PER_SEC);
}
