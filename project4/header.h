#ifndef __HEADER_H__
#define __HEADER_H__
struct Matrix
{
    long long row;
    long long column;
    float * content;
};
int matrixIsValid(const char * matrixString);                                  //检测输入格式
int valueIsValid(char c);                                                      //检测输入元素值
char * substr(const char * const string,int pos,int len);                      //截取字符串
struct Matrix createMatrix(const char * matrixString);                         //用输入的字符串创建矩阵
struct Matrix createZeros(long long row,long long column);                     //创建一个元素全为0的矩阵
struct Matrix createOnes(long long row,long long column);                      //创建一个元素全为1的矩阵
struct Matrix createRand(long long row,long long column,int range);            //创建一个元素在[0,range]随机取值的矩阵
void deleteMatrix(struct Matrix * mpointer);                                   //删除矩阵
void displayMatrix(const struct Matrix matrix);                                //打印矩阵
void printShape(struct Matrix matrix);                                         //打印矩阵的大小
void copyMatrix(struct Matrix * mpointer,const struct Matrix templateMatrix);  //复制矩阵
void reshapeMatrix(struct Matrix * mpointer,long long row,long long column);   //重构矩阵
struct Matrix transposeMatrix(struct Matrix matrix);                           //矩阵转置
struct Matrix addMatrix(struct Matrix matrix1,struct Matrix matrix2);          //矩阵相加
struct Matrix subtractMatrix(struct Matrix matrix1,struct Matrix matrix2);     //矩阵相减
struct Matrix matmul_plain(struct Matrix matrix1,struct Matrix matrix2);       //矩阵相乘(标准)
struct Matrix matmul_improved_1(struct Matrix matrix1,struct Matrix matrix2);  //矩阵相乘(1.0)
struct Matrix matmul_improved_2(struct Matrix matrix1,struct Matrix matrix2);  //矩阵相乘(2.0)
struct Matrix matmul_improved_3(struct Matrix matrix1,struct Matrix matrix2);  //矩阵相乘(3.0)  
struct Matrix addScalar(struct Matrix matrix,float scalar);                    //矩阵加标量
struct Matrix subtractScalar(struct Matrix matrix,float scalar);               //矩阵减标量
struct Matrix multiplyScalar(struct Matrix matrix,float scalar);               //矩阵数乘
float max(struct Matrix matrix);                                               //求矩阵内元素的最大值
float min(struct Matrix matrix);                                               //求矩阵内元素的最小值
float mean(struct Matrix matrix);                                              //求矩阵内元素的平均值
float sum(struct Matrix matrix);                                               //求矩阵内所有元素的和
#endif
