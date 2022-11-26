#include "header.h"

bool matrixIsValid(const char * matrixString)
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
        return false;
    }
    else
    {
        return true;
    }
} 
bool valueIsValid(char c)
{
    if((c>='0'&&c<='9')||c=='.'||c=='-')
    {
        return true;
    }
    else
    {
        return false;
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

struct Matrix * createMatrix(const char * matrixString)
{
    int isValid=1;
    struct Matrix * mpointer=NULL;
    if(!matrixIsValid(matrixString))
    {
        fprintf(stderr,"Failed to create a matrix because of invalid input!\n");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for a matrix!\n");
        return NULL;
    }
    if(matrixString[1]=='[')     //二维矩阵
    {
        long long row=1;
        long long column=1;
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
        mpointer->row=row;
        mpointer->column=column;
        mpointer->content=(float *)malloc(4*row*column);
        if(mpointer->content==NULL)
        {
            fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
            free(mpointer);
            return NULL;
        }
        //提取
        int splace=2,pos=2,mplace=0;
        for(;splace<strlen(matrixString);splace++)
        {
            if(matrixString[splace]!=','&&matrixString[splace]!=']')
            {
                if(!valueIsValid(matrixString[splace]))
                {
                    isValid=0;
                    break;
                }
            }
            else
            {
                mpointer->content[mplace]=atof(substr(matrixString,pos,splace-pos));
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
            return mpointer;
        }
        else
        {
            fprintf(stderr,"Failed to create a matrix because of invalid input!\n");
            free(mpointer);
            return NULL;
        }
    }
    else                         //一维向量
    {
        long long column=1;
        //确定列数
        for(int pos=1;pos<strlen(matrixString)-1;pos++)
        {
            if(matrixString[pos]==',')
            {
                column++;
            }
        }
        mpointer->row=1;
        mpointer->column=column;
        mpointer->content=(float *)malloc(4*column);
        if(mpointer->content==NULL)
        {
            fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
            free(mpointer);
            return NULL;
        }
        int splace=1,pos=1,mplace=0;
        for(;splace<strlen(matrixString);splace++)
        {
            if(matrixString[splace]!=','&&matrixString[splace]!=']')
            {
                if(!valueIsValid(matrixString[splace]))
                {
                    isValid=0;
                    break;
                }
            }
            else
            {
                mpointer->content[mplace]=atof(substr(matrixString,pos,splace-pos));
                pos=splace+1;
                mplace++;
            }
        }
        if(isValid==1)
        {
            return mpointer;
        }
        else
        {
            fprintf(stderr,"Failed to create a matrix because of invalid input!\n");
            free(mpointer);
            return NULL;
        }
    }
}

struct Matrix * createZeros(long long row,long long column)
{
    struct Matrix * mpointer=NULL;
    if(row<=0||column<=0)
    {
        fprintf(stderr,"Failed to create a matrix because of invalid input!\n");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for a matrix!\n");
        return NULL;
    }
    mpointer->row=row;
    mpointer->column=column;
    mpointer->content=(float *)malloc(4*row*column);
    if(mpointer->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
        free(mpointer);
        return NULL;
    }
    for(long long pos=0;pos<row*column;pos++)
    {
        mpointer->content[pos]=0;
    }
    return mpointer;
}

struct Matrix * createOnes(long long row,long long column)
{
    struct Matrix * mpointer=NULL;
    if(row<=0||column<=0)
    {
        fprintf(stderr,"Failed to create a matrix because of invalid input!\n");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for a matrix!\n");
        return NULL;
    }
    mpointer->row=row;
    mpointer->column=column;
    mpointer->content=(float *)malloc(4*row*column);
    if(mpointer->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
        free(mpointer);
        return NULL;
    }
    for(long long pos=0;pos<row*column;pos++)
    {
        mpointer->content[pos]=1;
    }
    return mpointer;
}

struct Matrix * createRand(long long row,long long column,int range)
{
    struct Matrix * mpointer=NULL;
    if(row<=0||column<=0)
    {
        fprintf(stderr,"Failed to create a matrix because of invalid input!\n");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for a matrix!\n");
        return NULL;
    }
    mpointer->row=row;
    mpointer->column=column;
    mpointer->content=(float *)malloc(4*row*column);
    if(mpointer->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
        free(mpointer);
        return NULL;
    }
    srand(time(0));
    for(long long pos=0;pos<row*column;pos++)
    {
        mpointer->content[pos]=(float)(rand()%(range+1));
    }
    return mpointer;
}

bool deleteMatrix(struct Matrix * matrix)
{
    if(matrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return false;
    }
    if(matrix->content!=NULL)
    {
        matrix->row=0;
        matrix->column=0;
        free(matrix->content);
        matrix->content=NULL;
    }
    return true;
}

bool displayMatrix(const struct Matrix * matrix)
{
    if(matrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return false;
    }
    else if(matrix->content==NULL)
    {
        fprintf(stderr,"The matrix you display doesn't exist!\n");
        return false;
    }
    if(matrix->row==1)
    {
        printf("[");
        int col=0;
        for(;col<matrix->column-1;col++)
        {
            printf("%.2f,",matrix->content[col]);
        }
        printf("%.2f]\n\n",matrix->content[col]);
    }
    else
    {
        printf("[[");
        int row=0;
        int col=0;
        for(;row<matrix->row-1;row++)
        {
            col=0;
            for(;col<matrix->column-1;col++){
                printf("%.2f,",matrix->content[row*matrix->column+col]);
            }
            printf("%.2f],\n[",matrix->content[row*matrix->column+col]);
        }
        col=0;
        for(;col<matrix->column-1;col++)
        {
            printf("%.2f,",matrix->content[row*matrix->column+col]);
        }
        printf("%.2f]]\n\n",matrix->content[row*matrix->column+col]);
    }
    return true;
}

bool printShape(const struct Matrix * matrix)
{
    if(matrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return false;
    }
    else if(matrix->content==NULL)
    {
        fprintf(stderr,"The matrix doesn't exist!\n");
        return false;
    }
    printf("(%lld,%lld)\n",matrix->row,matrix->column);
    return true;
}

bool copyMatrix(struct Matrix * matrix,const struct Matrix * templateMatrix)
{
    if(templateMatrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return false;
    }
    else if(templateMatrix->content==NULL)
    {
        fprintf(stderr,"The matrix you copy doesn't exist!\n");
        return false;
    }
    bool b=deleteMatrix(matrix);
    if(!b)
    {
        fprintf(stderr,"Failed to delete the matrix!\n");
        return false;
    }
    matrix->row=templateMatrix->row;
    matrix->column=templateMatrix->column;
    matrix->content=(float *)malloc(4*templateMatrix->row*templateMatrix->column);
    if(matrix->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix!\n");
        return false;
    }
    void * p=memcpy(templateMatrix->content,matrix->content,4*matrix->row*matrix->column);
    return true;
}

bool reshapeMatrix(struct Matrix * matrix,long long row,long long column)
{
    if(matrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return false;
    }
    else if(matrix->content==NULL)
    {
        printf("The matrix you reshape doesn't exist!\n");
        return false;
    }
    
    if(row*column!=(matrix->row)*(matrix->column))
    {
        fprintf(stderr,"Failed to reshape the matrix because of different size!\n");
        return false;
    }
    else if(row<=0||column<=0)
    {
        printf("Failed to reshape the matrix with such a row and column!\n");
        return false;
    }
    matrix->row=row;
    matrix->column=column;
    return true;
}

struct Matrix * transposeMatrix(const struct Matrix * matrix)
{
    struct Matrix * mpointer=NULL;
    if(matrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix->content==NULL)
    {
        printf("The matrix doesn't exist!");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix!\n");
        return NULL;
    }
    long long row=matrix->column;
    long long col=matrix->row;
    mpointer->row=row;
    mpointer->column=col;
    mpointer->content=(float *)malloc(4*row*col);
    if(mpointer->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
        free(mpointer);
        return NULL;
    }
    for(long long rowpos=0;rowpos<row;rowpos++)
    {
        for(long long colpos=0;colpos<col;colpos++)
        {
            mpointer->content[rowpos*col+colpos]=matrix->content[rowpos+colpos*matrix->column];
        }
    }
    return mpointer;
}

struct Matrix * addMatrix(const struct Matrix * matrix1,const struct Matrix * matrix2)
{
    struct Matrix * mpointer=NULL;
    if(matrix1==NULL)
    {
        fprintf(stderr,"The first input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix1->content==NULL)
    {
        fprintf(stderr,"The first matrix you add doesn't exist!\n");
        return NULL;
    }
    if(matrix2==NULL)
    {
        fprintf(stderr,"The second input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix2->content==NULL)
    {
        fprintf(stderr,"The second matrix you add doesn't exist!\n");
        return NULL;
    }
    if(matrix1->row!=matrix2->row||matrix1->column!=matrix2->column)
    {
        fprintf(stderr,"Failed to add two matrices because of different size!\n");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix!\n");
        return NULL;
    }
    long long row=matrix1->row;
    long long col=matrix1->column;
    mpointer->row=row;
    mpointer->column=col;
    mpointer->content=(float *)malloc(4*row*col);
    if(mpointer->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
        free(mpointer);
        return NULL;
    }
    for(long long pos=0;pos<row*col;pos++)
    {
        mpointer->content[pos]=matrix1->content[pos]+matrix2->content[pos];
    }
    return mpointer;         
}

struct Matrix * subtractMatrix(const struct Matrix * matrix1,const struct Matrix * matrix2)
{
    struct Matrix * mpointer=NULL;
    if(matrix1==NULL)
    {
        fprintf(stderr,"The first input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix1->content==NULL)
    {
        fprintf(stderr,"The first matrix you add doesn't exist!\n");
        return NULL;
    }
    if(matrix2==NULL)
    {
        fprintf(stderr,"The second input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix2->content==NULL)
    {
        fprintf(stderr,"The second matrix you add doesn't exist!\n");
        return NULL;
    }
    if(matrix1->row!=matrix2->row||matrix1->column!=matrix2->column)
    {
        fprintf(stderr,"Failed to subtract two matrices because of different size!\n");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix!\n");
        return NULL;
    }
    long long row=matrix1->row;
    long long col=matrix1->column;
    mpointer->row=row;
    mpointer->column=col;
    mpointer->content=(float *)malloc(4*row*col);
    if(mpointer->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
        free(mpointer);
        return NULL;
    }
    for(long long pos=0;pos<row*col;pos++)
    {
        mpointer->content[pos]=matrix1->content[pos]-matrix2->content[pos];
    }
    return mpointer;         
}

struct Matrix * matmul_plain(const struct Matrix * matrix1,const struct Matrix * matrix2)
{
    struct Matrix * mpointer=NULL;
    if(matrix1==NULL)
    {
        fprintf(stderr,"The first input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix1->content==NULL)
    {
        fprintf(stderr,"The first matrix you add doesn't exist!\n");
        return NULL;
    }
    if(matrix2==NULL)
    {
        fprintf(stderr,"The second input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix2->content==NULL)
    {
        fprintf(stderr,"The second matrix you add doesn't exist!\n");
        return NULL;
    }
    if(matrix1->column!=matrix2->row)
    {
        fprintf(stderr,"Failed to multiply two matrices because of different column and row!\n");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix!\n");
        return NULL;
    }
    mpointer->row=matrix1->row;
    mpointer->column=matrix2->column;
    mpointer->content=(float *)malloc(4*mpointer->row*mpointer->column);
    if(mpointer->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
        free(mpointer);
        return NULL;
    }
    long long pos=0;
    for(long long rowpos=0;rowpos<matrix1->row;rowpos++)
    {
        for(long long colpos1=0;colpos1<matrix2->column;colpos1++,pos++)
        {
            float value=0;
            for(long long colpos2=0;colpos2<matrix1->column;colpos2++)
            {
                value+=(matrix1->content[rowpos*matrix1->column+colpos2]*matrix2->content[colpos1+colpos2*matrix2->column]);
            }
            mpointer->content[pos]=value;
        }
    }
    return mpointer;
}

struct Matrix * matmul_improved(const struct Matrix * matrix1,const struct Matrix * matrix2)
{
    struct Matrix * mpointer=NULL;
    if(matrix1==NULL)
    {
        fprintf(stderr,"The first input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix1->content==NULL)
    {
        fprintf(stderr,"The first matrix you add doesn't exist!\n");
        return NULL;
    }
    if(matrix2==NULL)
    {
        fprintf(stderr,"The second input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix2->content==NULL)
    {
        fprintf(stderr,"The second matrix you add doesn't exist!\n");
        return NULL;
    }
    if(matrix1->column!=matrix2->row)
    {
        fprintf(stderr,"Failed to multiply two matrices because of different column and row!\n");
        return NULL;
    }
    else if(matrix1->column%8!=0||matrix2->row%8!=0)
    {
        fprintf(stderr,"Failed to multiply two matrices because the column and row are not the multiple of 8!\n");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix!\n");
        return NULL;
    }
    mpointer->row=matrix1->row;
    mpointer->column=matrix2->column;
    mpointer->content=(float *)malloc(4*mpointer->row*mpointer->column);
    if(mpointer->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
        free(mpointer);
        return NULL;
    }
    long long rowpos=0;
    long long colpos=0;
    long long idx=0;
    for(;colpos<matrix2->column;colpos++)
    {
        for(idx=0;idx<matrix1->column;idx+=8)
        {
            float sum[8]={0};
            __m256 mat,mat1;
            __m256 mat2=_mm256_set_ps(matrix2->content[colpos+idx*matrix2->column],matrix2->content[colpos+(idx+1)*matrix2->column],\
                                matrix2->content[colpos+(idx+2)*matrix2->column],matrix2->content[colpos+(idx+3)*matrix2->column],\
                                matrix2->content[colpos+(idx+4)*matrix2->column],matrix2->content[colpos+(idx+5)*matrix2->column],\
                                matrix2->content[colpos+(idx+6)*matrix2->column],matrix2->content[colpos+(idx+7)*matrix2->column]);
            #pragma omp parallel for
            for(rowpos=0;rowpos<matrix1->row;rowpos++)
            {
                mat=_mm256_setzero_ps();
                mat1=_mm256_loadu_ps(matrix1->content+rowpos*matrix1->column+idx);
                mat=_mm256_add_ps(mat,_mm256_mul_ps(mat1,mat2));
                _mm256_storeu_ps(sum,mat);
                mpointer->content[rowpos*matrix2->column+colpos]+=(sum[0]+sum[1]+sum[2]+sum[3]+sum[4]+sum[5]+sum[6]+sum[7]);
            } 
        }
    }
    return mpointer;
}

struct Matrix * matmul_improved_2(const struct Matrix * matrix1,const struct Matrix * matrix2)
{
    struct Matrix * mpointer=NULL;
    if(matrix1==NULL)
    {
        fprintf(stderr,"The first input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix1->content==NULL)
    {
        fprintf(stderr,"The first matrix you add doesn't exist!\n");
        return NULL;
    }
    if(matrix2==NULL)
    {
        fprintf(stderr,"The second input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix2->content==NULL)
    {
        fprintf(stderr,"The second matrix you add doesn't exist!\n");
        return NULL;
    }
    if(matrix1->column!=matrix2->row)
    {
        fprintf(stderr,"Failed to multiply two matrices because of different column and row!\n");
        return NULL;
    }
    else if(matrix1->column%16!=0||matrix2->row%16!=0)
    {
        fprintf(stderr,"Failed to multiply two matrices because the column and row are not the multiple of 8!\n");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix!\n");
        return NULL;
    }
    mpointer->row=matrix1->row;
    mpointer->column=matrix2->column;
    mpointer->content=(float *)malloc(4*mpointer->row*mpointer->column);
    if(mpointer->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
        free(mpointer);
        return NULL;
    }
    struct Matrix * matrix3=transposeMatrix(matrix2);
    long long rowpos=0;
    long long colpos=0;
    long long idx=0;
    do
    {
        colpos=0;
        do
        {
            float sum[16]={0};
            __m512 mat1,mat2;
            __m512 mat=_mm512_setzero_ps();
            #pragma omp parallel for
            for(idx=0;idx<matrix1->column;idx+=16)
            {
                mat1=_mm512_loadu_ps(matrix1->content+rowpos*matrix1->column+idx);
                mat2=_mm512_loadu_ps(matrix3->content+colpos*matrix3->column+idx);
                mat=_mm512_add_ps(mat,_mm512_mul_ps(mat1,mat2));
            } 
            _mm512_storeu_ps(sum,mat);
            mpointer->content[rowpos*matrix3->row+colpos]=(sum[0]+sum[1]+sum[2]+sum[3]+sum[4]+sum[5]+sum[6]+sum[7]+sum[8]+sum[9]+sum[10]+sum[11]+sum[12]+sum[13]+sum[14]+sum[15]);
            colpos++;
        }while(colpos<matrix3->row);
        rowpos++;
    }while(rowpos<matrix1->row);
    return mpointer;
}


struct Matrix * addScalar(const struct Matrix * matrix,float scalar)
{
    struct Matrix * mpointer=NULL;
    if(matrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix->content==NULL)
    {
        fprintf(stderr,"The matrix doesn't exist!\n");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix!\n");
        return NULL;
    }
    long long row=matrix->row;
    long long col=matrix->column;
    mpointer->row=row;
    mpointer->column=col;
    mpointer->content=(float *)malloc(4*row*col);
    if(mpointer->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
        free(mpointer);
        return NULL;
    }
    for(long long pos=0;pos<row*col;pos++)
    {
        mpointer->content[pos]=matrix->content[pos]+scalar;
    }
    return mpointer;
}

struct Matrix * subtractScalar(const struct Matrix * matrix,float scalar)
{
    struct Matrix * mpointer=NULL;
    if(matrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix->content==NULL)
    {
        fprintf(stderr,"The matrix doesn't exist!\n");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix!\n");
        return NULL;
    }
    long long row=matrix->row;
    long long col=matrix->column;
    mpointer->row=row;
    mpointer->column=col;
    mpointer->content=(float *)malloc(4*row*col);
    if(mpointer->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
        free(mpointer);
        return NULL;
    }
    for(long long pos=0;pos<row*col;pos++)
    {
        mpointer->content[pos]=matrix->content[pos]-scalar;
    }
    return mpointer;
}

struct Matrix * multiplyScalar(const struct Matrix * matrix,float scalar)
{
    struct Matrix * mpointer=NULL;
    if(matrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return NULL;
    }
    else if(matrix->content==NULL)
    {
        fprintf(stderr,"The matrix doesn't exist!\n");
        return NULL;
    }
    mpointer=(struct Matrix *)malloc(sizeof(struct Matrix));
    if(mpointer==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix!\n");
        return NULL;
    }
    long long row=matrix->row;
    long long col=matrix->column;
    mpointer->row=row;
    mpointer->column=col;
    mpointer->content=(float *)malloc(4*row*col);
    if(mpointer->content==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the matrix's content!\n");
        free(mpointer);
        return NULL;
    }
    for(long long pos=0;pos<row*col;pos++)
    {
        mpointer->content[pos]=matrix->content[pos]*scalar;
    }
    return mpointer;
}

float max(const struct Matrix * matrix)
{
    if(matrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return 0;
    }
    else if(matrix->content==NULL)
    {
        fprintf(stderr,"The matrix doesn't exist!\n");
        return 0;
    }
    float max=-999999.0f;
    for(long long pos=0;pos<matrix->row*matrix->column;pos++)
    {
        max=matrix->content[pos]>max?matrix->content[pos]:max;
    }
    return max;
}
float min(const struct Matrix * matrix)
{
    if(matrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return 0;
    }
    else if(matrix->content==NULL)
    {
        fprintf(stderr,"The matrix doesn't exist!\n");
        return 0;
    }
    float min=999999.0f;
    for(long long pos=0;pos<matrix->row*matrix->column;pos++)
    {
        min=matrix->content[pos]<min?matrix->content[pos]:min;
    }
    return min;
}

float mean(const struct Matrix * matrix)
{
    if(matrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return 0;
    }
    else if(matrix->content==NULL)
    {
        fprintf(stderr,"The matrix doesn't exist!\n");
        return 0;
    }
    float total=0.0f;
    for(long long pos=0;pos<matrix->row*matrix->column;pos++)
    {
        total+=matrix->content[pos];
    }
    return total/(float)(matrix->row*matrix->column);
}

float sum(const struct Matrix * matrix)
{
    if(matrix==NULL)
    {
        fprintf(stderr,"The input matrix pointer doesn't exist!\n");
        return 0;
    }
    else if(matrix->content==NULL)
    {
        fprintf(stderr,"The matrix doesn't exist!\n");
        return 0;
    }
    float total=0.0f;
    for(long long pos=0;pos<matrix->row*matrix->column;pos++)
    {
        total+=matrix->content[pos];
    }
    return total;
}




