#ifndef TEST_OPENBLAS
#define TEST_OPENBLAS
#include <cblas.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#endif

int main()
{
    clock_t time_start,time_end;
    int N=16;
    long long length=16*16;
    float * matrix1=(float *)malloc(4*length);
    float * matrix2=(float *)malloc(4*length);
    float * matrix3=(float *)malloc(4*length);
    srand(time(0));
    for(long long pos=0;pos<length;pos++)
    {
        matrix1[pos]=(float)(rand()%(10));
        matrix2[pos]=(float)(rand()%(10));
    }
    time_start=clock();
    cblas_sgemm(CblasRowMajor,CblasConjNoTrans,CblasConjNoTrans,N,N,N,1,matrix1,N,matrix2,N,0,matrix3,N);
    time_end=clock();
    printf("OpenBLAS: %fs\n",(double)(time_end-time_start)/CLOCKS_PER_SEC);
    free(matrix1);
    free(matrix2);
    free(matrix3);
    return 0;
}
