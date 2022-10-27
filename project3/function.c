#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "header.h"

int matrixIsValid(const char * matrixString)
{
    int cnt1=0;   //存储'['的个数
    int cnt2=0;   //存储']'的个数
    int cnt3=1;   //存储','的个数
    int col=1;    //存储列数
    int isValid=1;
    for(int pos=0;pos<strlen(matrixString);pos++)
    {
        if(matrixString[pos]=='[')
        {
            cnt1++;
        }
        else if(matrixString[pos]==']')
        {
            cnt2++;
        }
    }
    //确定列数
    for(int pos=0;pos<strlen(matrixString);pos++)
    {
        if(matrixString[pos]==',')
        {
            col++;
        }
        if(matrixString[pos]==']')
        {
            break;
        }
    }
    //检测每行元素个数是否相等
    for(int pos=0;pos<strlen(matrixString);pos++)
    {
        if(matrixString[pos]==',')
        {
            cnt3++;
        }
        else if(matrixString[pos]==']')
        {
            if(cnt3!=col)
            {
                isValid=0;
                break;
            }
            else
            {
                cnt3=1;
                pos+=2;
            }
        }
    }
    if(cnt1!=cnt2||isValid==0)   //两种invalid情况：1.'['或']'缺失；2.每行元素的个数不相等
    {
        return 0;
    }
    else
    {
        return 1;
    }
} 
int valueIsValid(char c)
{
    if((c>='0'&&c<='9')||c=='.'||c=='-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}               

char * substr(const char * const string,int pos,int len)
{
    int length=strlen(string);
    if(len>length-pos){
        len=length-pos;
    }
    char * substring=(char *)malloc(1);
    for(int subplace=0,strplace=pos;subplace<len;subplace++,strplace++){
        substring[subplace]=string[strplace];
    }
    return substring;
    free(substring);
}

struct Matrix createMatrix(const char * matrixString)
{
    int isValid=1;
    if(matrixIsValid(matrixString)==0)
    {
        printf("Unable to create matrix because of invalid input!\n");
        struct Matrix result={0,0,NULL};
        return result;
    }
    else
    {
        if(matrixString[1]=='[')     //二维矩阵
        {
            int row=1;
            int column=1;
            //确定行数和列数
            for(int pos=2;pos<strlen(matrixString)-2;pos++)
            {
                if(matrixString[pos]==']')
                {
                    row++;
                }
            }
            for(int pos=2;pos<strlen(matrixString)-2;pos++)
            {
                if(matrixString[pos]==',')
                {
                    column++;
                }
                if(matrixString[pos]==']')
                {
                    break;
                }
            }
            float * mpointer=(float *)malloc(4*row*column);
            //提取
            int splace=2,pos=2,mplace=0;
            for(;splace<strlen(matrixString);splace++)
            {
                if(matrixString[splace]!=','&&matrixString[splace]!=']')
                {
                    if(valueIsValid(matrixString[splace])==0)
                    {
                        isValid=0;
                        break;
                    }
                }
                else
                {
                    mpointer[mplace]=atof(substr(matrixString,pos,splace-pos));
                    pos=splace+1;
                    mplace++;
                    //是否在每行的最后（除最后一行）
                    if(matrixString[splace]==']'&&matrixString[splace+1]!=']')
                    {
                        splace+=3;
                        pos=splace;
                        continue;
                    }
                    //是否在最后一行的最后
                    else if(matrixString[splace]==']'&&matrixString[splace+1]==']')
                    {
                        break;
                    }
                }
            }
            if(isValid==1)
            {
                struct Matrix result={row,column,mpointer};
                return result;
            }
            else
            {
                printf("Unable to create matrix because of invalid input!\n");
                struct Matrix result={0,0,NULL};
                return result;
            }
            free(mpointer);
        }
        else                         //一维向量
        {
            int column=1;
            //确定列数
            for(int pos=1;pos<strlen(matrixString)-1;pos++)
            {
                if(matrixString[pos]==',')
                {
                    column++;
                }
            }
            float * mpointer=(float *)malloc(4*column);
            int splace=1,pos=1,mplace=0;
            for(;splace<strlen(matrixString);splace++)
            {
                if(matrixString[splace]!=','&&matrixString[splace]!=']')
                {
                    if(valueIsValid(matrixString[splace])==0)
                    {
                        isValid=0;
                        break;
                    }
                }
                else
                {
                    mpointer[mplace]=atof(substr(matrixString,pos,splace-pos));
                    pos=splace+1;
                    mplace++;
                }
            }
            if(isValid==1)
            {
                struct Matrix result={1,column,mpointer};
                return result;
            }
            else
            {
                printf("Unable to create matrix because of invalid input!\n");
                struct Matrix result={0,0,NULL};
                return result;
            }
            free(mpointer);
        }
    }
}

struct Matrix createZeros(int row,int column)
{
    if(row>0&&column>0)
    {
        float * mpointer=(float *)malloc(4*row*column);
        for(int pos=0;pos<row*column;pos++)
        {
            mpointer[pos]=0;
        }
        struct Matrix result={row,column,mpointer};
        return result;
        free(mpointer);
    }
    else
    {
        printf("Can not create a matrix with such row and column!");
        struct Matrix result={0,0,NULL};
        return result;
    }
}

struct Matrix createOnes(int row,int column)
{
    if(row>0&&column>0)
    {
        float * mpointer=(float *)malloc(4*row*column);
        for(int pos=0;pos<row*column;pos++)
        {
            mpointer[pos]=1;
        }
        struct Matrix result={row,column,mpointer};
        return result;
        free(mpointer);
    }
    else
    {
        printf("Can not create a matrix with such row and column!");
        struct Matrix result={0,0,NULL};
        return result;
    }
}

struct Matrix createRand(int row,int column,int range)
{
    if(row>0&&column>0)
    {
        float * mpointer=(float *)malloc(4*row*column);
        srand(time(0));
        for(int pos=0;pos<row*column;pos++)
        {
            mpointer[pos]=(float)(rand()%(range+1));
        }
        struct Matrix result={row,column,mpointer};
        return result;
        free(mpointer);
    }
    else
    {
        printf("Can not create a matrix with such row and column!");
        struct Matrix result={0,0,NULL};
        return result;
    }
}

void deleteMatrix(struct Matrix * mpointer)
{
    if(mpointer->content!=NULL){
        mpointer->row=0;
        mpointer->column=0;
        mpointer->content=NULL;
    }
}

void displayMatrix(const struct Matrix matrix)
{
    if(matrix.content==NULL)
    {
        printf("The matrix you display doesn't exist!\n");
    }
    else
    {
        if(matrix.row==1)
        {
            printf("[");
            int col=0;
            for(;col<matrix.column-1;col++)
            {
                printf("%.2f,",matrix.content[col]);
            }
            printf("%.2f]\n",matrix.content[col]);
        }
        else
        {
            printf("[[");
            int row=0;
            int col=0;
            for(;row<matrix.row-1;row++)
            {
                col=0;
                for(;col<matrix.column-1;col++){
                    printf("%.2f,",matrix.content[row*matrix.column+col]);
                }
                printf("%.2f],\n[",matrix.content[row*matrix.column+col]);
            }
            col=0;
            for(;col<matrix.column-1;col++)
            {
                printf("%.2f,",matrix.content[row*matrix.column+col]);
            }
            printf("%.2f]]\n",matrix.content[row*matrix.column+col]);
        }
    }
}

void copyMatrix(struct Matrix * mpointer,const struct Matrix templateMatrix)
{
    if(templateMatrix.content==NULL)
    {
        printf("The matrix you copy doesn't exist!\n");
    }
    else
    {
        mpointer->row=templateMatrix.row;
        mpointer->column=templateMatrix.column;
        mpointer->content=templateMatrix.content;
    }
}

void reshapeMatrix(struct Matrix * mpointer,int row,int column)
{
    if(mpointer->content==NULL)
    {
        printf("The matrix you reshape doesn't exist!\n");
    }
    else
    {
        if(row*column==(mpointer->row)*(mpointer->column))
        {
            mpointer->row=row;
            mpointer->column=column;
        }
        else
        {
            printf("Can not reshape the matrix with such a row and column!\n");
        }
    }
}

struct Matrix addMatrix(struct Matrix matrix1,struct Matrix matrix2)
{
    if(matrix1.content==NULL||matrix2.content==NULL)
    {
        printf("The matrix you add doesn't exist!\n");
        struct Matrix result={0,0,NULL};
        return result;
    }
    else
    {
        if(matrix1.row==matrix2.row&&matrix1.column==matrix2.column)
        {
            int row=matrix1.row;
            int col=matrix1.column;
            float * mpointer=(float *)malloc(4*row*col);
            for(int pos=0;pos<row*col;pos++)
            {
                mpointer[pos]=matrix1.content[pos]+matrix2.content[pos];
            }
            struct Matrix result={row,col,mpointer};
            return result;
            free(mpointer);
        }
        else
        {
            printf("Two matrices have different sizes, hence can not be added!\n");
            struct Matrix result={0,0,NULL};
            return result;
        }
    }
}

struct Matrix subtractMatrix(struct Matrix matrix1,struct Matrix matrix2)
{
    if(matrix1.content==NULL||matrix2.content==NULL)
    {
        printf("The matrix you subtract doesn't exist!\n");
        struct Matrix result={0,0,NULL};
        return result;
    }
    else
    {
        if(matrix1.row==matrix2.row&&matrix1.column==matrix2.column)
        {
            int row=matrix1.row;
            int col=matrix1.column;
            float * mpointer=(float *)malloc(4*row*col);
            for(int pos=0;pos<row*col;pos++)
            {
                mpointer[pos]=matrix1.content[pos]-matrix2.content[pos];
            }
            struct Matrix result={row,col,mpointer};
            return result;
            free(mpointer);
        }
        else
        {
            printf("Two matrices have different sizes, hence can not be subtracted!\n");
            struct Matrix result={0,0,NULL};
            return result;
        }
    }
}

struct Matrix multiplyMatrix(struct Matrix matrix1,struct Matrix matrix2)
{
    if(matrix1.content==NULL||matrix2.content==NULL)
    {
        printf("The matrix you multiply doesn't exist!\n");
        struct Matrix result={0,0,NULL};
        return result;
    }
    else
    {
        if(matrix1.column==matrix2.row)
        {
            int row=matrix1.row;
            int col=matrix2.column;
            float * mpointer=(float *)malloc(4*row*col);
            int pos=0;
            for(int rowpos=0;rowpos<matrix1.row;rowpos++)
            {
                for(int colpos1=0;colpos1<matrix2.column;colpos1++,pos++)
                {
                    float value=0;
                    for(int colpos2=0;colpos2<matrix1.column;colpos2++)
                    {
                        value+=(matrix1.content[rowpos*matrix1.column+colpos2]*matrix2.content[colpos1+colpos2*matrix2.column]);
                    }
                    mpointer[pos]=value;
                }
            }
            struct Matrix result={row,col,mpointer};
            return result;
            free(mpointer);
        }
        else
        {
            printf("The column of the former one is not equal to the latter one, hence can not be multiplied!\n");
            struct Matrix result={0,0,NULL};
            return result;
        }
    }
}

struct Matrix addScalar(struct Matrix matrix,float scalar)
{
    if(matrix.content==NULL)
    {
        printf("The matrix doesn't exist!\n");
        struct Matrix result={0,0,NULL};
        return result;
    }
    else
    {
        int row=matrix.row;
        int col=matrix.column;
        float * mpointer=(float *)malloc(4*row*col);
        for(int pos=0;pos<row*col;pos++)
        {
            mpointer[pos]=matrix.content[pos]+scalar;
        }
        struct Matrix result={row,col,mpointer};
        return result;
        free(mpointer);
    }
}

struct Matrix subtractScalar(struct Matrix matrix,float scalar)
{
    if(matrix.content==NULL)
    {
        printf("The matrix doesn't exist!\n");
        struct Matrix result={0,0,NULL};
        return result;
    }
    else
    {
        int row=matrix.row;
        int col=matrix.column;
        float * mpointer=(float *)malloc(4*row*col);
        for(int pos=0;pos<row*col;pos++)
        {
            mpointer[pos]=matrix.content[pos]-scalar;
        }
        struct Matrix result={row,col,mpointer};
        return result;
        free(mpointer);
    }
}

struct Matrix multiplyScalar(struct Matrix matrix,float scalar)
{
    if(matrix.content==NULL)
    {
        printf("The matrix doesn't exist!\n");
        struct Matrix result={0,0,NULL};
        return result;
    }
    else
    {
        int row=matrix.row;
        int col=matrix.column;
        float * mpointer=(float *)malloc(4*row*col);
        for(int pos=0;pos<row*col;pos++)
        {
            mpointer[pos]=matrix.content[pos]*scalar;
        }
        struct Matrix result={row,col,mpointer};
        return result;
        free(mpointer);
    }
}

float max(struct Matrix matrix)
{
    if(matrix.content==NULL)
    {
        printf("The matrix doesn't exist!\n");
        return 0;
    }
    else
    {
        float max=-9999999;
        for(int pos=0;pos<matrix.row*matrix.column;pos++)
        {
            max=matrix.content[pos]>max?matrix.content[pos]:max;
        }
        return max;
    }
}
float min(struct Matrix matrix)
{
    if(matrix.content==NULL)
    {
        printf("The matrix doesn't exist!\n");
        return 0;
    }
    else
    {
        float min=9999999;
        for(int pos=0;pos<matrix.row*matrix.column;pos++)
        {
            min=matrix.content[pos]<min?matrix.content[pos]:min;
        }
        return min;
    }
}

float mean(struct Matrix matrix)
{
    if(matrix.content==NULL)
    {
        printf("The matrix doesn't exist!\n");
        return 0;
    }
    else
    {
        float total=0;
        for(int pos=0;pos<matrix.row*matrix.column;pos++)
        {
            total+=matrix.content[pos];
        }
        return total/(matrix.row*matrix.column);
    }
}

float sum(struct Matrix matrix)
{
    if(matrix.content==NULL)
    {
        printf("The matrix doesn't exist!\n");
        return 0;
    }
    else
    {
        float total=0;
        for(int pos=0;pos<matrix.row*matrix.column;pos++)
        {
            total+=matrix.content[pos];
        }
        return total;
    }
}
