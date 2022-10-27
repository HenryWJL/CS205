#ifndef __HEADER_H__
#define __HEADER_H__
struct Matrix
{
    int row;
    int column;
    float * content;
};
int matrixIsValid(const char * matrixString);                                  //检测输入格式
int valueIsValid(char c);                                                      //检测输入元素值
char * substr(const char * const string,int pos,int len);                      //截取字符串
struct Matrix createMatrix(const char * matrixString);                         //用输入的字符串创建矩阵
struct Matrix createZeros(int row,int column);                                 //创建一个元素全为0的矩阵
struct Matrix createOnes(int row,int column);                                  //创建一个元素全为1的矩阵
struct Matrix createRand(int row,int column,int range);                        //创建一个元素在[0,range]随机取值的矩阵
void deleteMatrix(struct Matrix * mpointer);                                   //删除矩阵
void displayMatrix(const struct Matrix matrix);                                //在terminal中打印矩阵
void copyMatrix(struct Matrix * mpointer,const struct Matrix templateMatrix);  //复制矩阵
void reshapeMatrix(struct Matrix * mpointer,int row,int column);               //重构矩阵
struct Matrix addMatrix(struct Matrix matrix1,struct Matrix matrix2);          //矩阵相加
struct Matrix subtractMatrix(struct Matrix matrix1,struct Matrix matrix2);     //矩阵相减
struct Matrix multiplyMatrix(struct Matrix matrix1,struct Matrix matrix2);     //矩阵相乘
struct Matrix addScalar(struct Matrix matrix,float scalar);                    //矩阵加标量
struct Matrix subtractScalar(struct Matrix matrix,float scalar);               //矩阵减标量
struct Matrix multiplyScalar(struct Matrix matrix,float scalar);               //矩阵数乘
float max(struct Matrix matrix);                                               //求矩阵内元素的最大值
float min(struct Matrix matrix);                                               //求矩阵内元素的最小值
float mean(struct Matrix matrix);                                              //求矩阵内元素的平均值
float sum(struct Matrix matrix);                                               //求矩阵内所有元素的和
#endif
