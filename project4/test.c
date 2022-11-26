#include "header.h"

int main()
{
    clock_t time_start,time_end;
    struct Matrix * matrix1=createRand(16,16,9);
    struct Matrix * matrix2=createRand(16,16,9);

    time_start=clock();
    struct Matrix * matrix3=matmul_plain(matrix1,matrix2);
    time_end=clock();
    printf("matmul_plain: %fs\n",(double)(time_end-time_start)/CLOCKS_PER_SEC);

    time_start=clock();
    struct Matrix * matrix4=matmul_improved(matrix1,matrix2);
    time_end=clock();
    printf("matmul_improved: %fs\n",(double)(time_end-time_start)/CLOCKS_PER_SEC);

    time_start=clock();
    struct Matrix * matrix5=matmul_improved_2(matrix1,matrix2);
    time_end=clock();
    printf("matmul_improved_2: %fs\n",(double)(time_end-time_start)/CLOCKS_PER_SEC);

    free(matrix1);
    free(matrix2);
    return 0;
}
