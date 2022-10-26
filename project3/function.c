#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "header.h"

int matrixIsValid(const char * matrixString)
{
    return 1;
} 
int valueIsValid(char c)
{
    if((c>='0'&&c<='9')||c=='.')
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
    float * mpointer=(float *)malloc(4);
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
            struct Matrix result={0,0,NULL};
            return result;
        }
        else                         //一维向量
        {
            int splace=1,pos=1,mplace=0;
            for(;splace<strlen(matrixString)-1;splace++)
            {
                if(matrixString[splace]!=',')
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
            mpointer[mplace]=atof(substr(matrixString,pos,splace-pos));
            if(isValid==1)
            {
                struct Matrix result={1,mplace+1,mpointer};
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

// struct Matrix createMatrix(int row,int column)
// {
//     float * marray=(float *)malloc(4);
//     int isValid=1;
//     for(int rownum=0;rownum<row;rownum++)
//     {
//         printf("Please input row No.%d: ",rownum+1);
//         for(int colnum=0;colnum<column;colnum++){
//             float value;
//             int state=scanf("%f",&value);
//             if(state==1)
//             {
//                 marray[rownum+colnum]=value;
//             }
//             else
//             {
//                 isValid=0;
//             }
//         }
//     }
//     if(isValid==0)
//     {
//         printf("Invalid");
//         struct Matrix matrix={0,0,NULL};
//         return matrix;
//     }
//     else
//     {
//         struct Matrix matrix={row,column,marray};
//         return matrix;
//         free(marray);
//     }
// }

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
            float * mpointer=(float *)malloc(4);
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

float maxValue(struct Matrix matrix)
{
    float max=-9999999;
    for(int pos=0;pos<matrix.row*matrix.column;pos++)
    {
        max=matrix.content[pos]>max?matrix.content[pos]:max;
    }
    return max;
}
float minValue(struct Matrix matrix)
{
    float min=9999999;
    for(int pos=0;pos<matrix.row*matrix.column;pos++)
    {
        min=matrix.content[pos]<min?matrix.content[pos]:min;
    }
    return min;
}

