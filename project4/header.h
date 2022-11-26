#ifndef __HEADER_H__
#define __HEADER_H__
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <immintrin.h>

struct Matrix
{
    long long row;
    long long column;
    float * content;
};
bool matrixIsValid(const char * matrixString);                                                   //检测输入格式
bool valueIsValid(char c);                                                                       //检测输入元素值
char * substr(const char * const string,int pos,int len);                                        //截取字符串
struct Matrix * createMatrix(const char * matrixString);                                         //用输入的字符串创建矩阵
struct Matrix * createZeros(long long row,long long column);                                     //创建一个元素全为0的矩阵
struct Matrix * createOnes(long long row,long long column);                                      //创建一个元素全为1的矩阵
struct Matrix * createRand(long long row,long long column,int range);                            //创建一个元素在[0,range]随机取值的矩阵
bool deleteMatrix(struct Matrix * matrix);                                                       //删除矩阵
bool displayMatrix(const struct Matrix * matrix);                                                //打印矩阵
bool printShape(const struct Matrix * matrix);                                                   //打印矩阵的大小
bool copyMatrix(struct Matrix * matrix,const struct Matrix * templateMatrix);                    //复制矩阵
bool reshapeMatrix(struct Matrix * matrix,long long row,long long column);                       //重构矩阵
struct Matrix * transposeMatrix(const struct Matrix * matrix);                                   //矩阵转置
struct Matrix * addMatrix(const struct Matrix * matrix1,const struct Matrix * matrix2);          //矩阵相加
struct Matrix * subtractMatrix(const struct Matrix * matrix1,const struct Matrix * matrix2);     //矩阵相减
struct Matrix * matmul_plain(const struct Matrix * matrix1,const struct Matrix * matrix2);       //矩阵相乘(标准)
struct Matrix * matmul_improved(const struct Matrix * matrix1,const struct Matrix * matrix2);    //矩阵相乘(1.0)
struct Matrix * matmul_improved_2(const struct Matrix * matrix1,const struct Matrix * matrix2);  //矩阵相乘(2.0)  
struct Matrix * addScalar(const struct Matrix * matrix,float scalar);                            //矩阵加标量
struct Matrix * subtractScalar(const struct Matrix * matrix,float scalar);                       //矩阵减标量
struct Matrix * multiplyScalar(const struct Matrix * matrix,float scalar);                       //矩阵数乘
float max(const struct Matrix * matrix);                                                         //求矩阵内元素的最大值
float min(const struct Matrix * matrix);                                                         //求矩阵内元素的最小值
float mean(const struct Matrix * matrix);                                                        //求矩阵内元素的平均值
float sum(const struct Matrix * matrix);                                                         //求矩阵内所有元素的和
#endif

