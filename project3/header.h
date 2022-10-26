#ifndef __HEADER_H__
#define __HEADER_H__
struct Matrix
{
    int row;
    int column;
    float * content;
};
int matrixIsValid(const char * matrixString); //检测输入矩阵的格式
int valueIsValid(char c);               //检测输入矩阵的元素值
char * substr(const char * const string,int pos,int len);
struct Matrix createMatrix(const char * matrixString);
struct Matrix createZeros(int row,int column);
struct Matrix createOnes(int row,int column);
struct Matrix createRand(int row,int column,int range);
void deleteMatrix(struct Matrix * mpointer);
void displayMatrix(const struct Matrix matrix);
void copyMatrix(struct Matrix * mpointer,const struct Matrix templateMatrix);
struct Matrix addMatrix(struct Matrix matrix1,struct Matrix matrix2);
struct Matrix subtractMatrix(struct Matrix matrix1,struct Matrix matrix2);
struct Matrix multiplyMatrix(struct Matrix matrix1,struct Matrix matrix2);
struct Matrix addScalar(struct Matrix matrix,float scalar);
struct Matrix subtractScalar(struct Matrix matrix,float scalar);
struct Matrix multiplyScalar(struct Matrix matrix,float scalar);
float max(struct Matrix matrix);
float min(struct Matrix matrix);
float mean(struct Matrix matrix);
float sum(struct Matrix matrix);
#endif
