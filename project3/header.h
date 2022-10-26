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
// struct Matrix createMatrix(int row,int column);
void deleteMatrix(struct Matrix * mpointer);
void displayMatrix(const struct Matrix matrix);
void copyMatrix(struct Matrix * mpointer,const struct Matrix templateMatrix);
struct Matrix addMatrix(struct Matrix matrix1,struct Matrix matrix2);
float maxValue(struct Matrix matrix);
float minValue(struct Matrix matrix);
#endif
