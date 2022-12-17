#ifndef __HEADER_HPP__
#define __HEADER_HPP__
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
using namespace std;

template<typename T>
class Mat
{
    size_t row;
    size_t column;
    size_t channel;
    T * data;
    int * count;
public:
    Mat(size_t row=0,size_t column=0,size_t channel=0,string option="zeros",T * data=NULL,size_t length=0):row(row),column(column),channel(channel)
    {
        if(this->row==0||this->column==0||this->channel==0)
        {
            this->row=0;
            this->column=0;
            this->channel=0;
            this->data=NULL;
        }
        else
        {
            this->data=new T[sizeof(T)*row*column*channel]{};
            if(option.compare("zeros")==0)
            {
                ;
            }
            else if(option.compare("ones")==0)
            {
                for(size_t idx=0;idx<row*column*channel;idx++)
                {
                    this->data[idx]=1;
                }
            }
            else if(option.compare("rand")==0)
            {
                for(size_t idx=0;idx<row*column*channel;idx++)
                {
                    this->data[idx]=(T)((rand()%1000)/100.0f);
                }
            }
            else if(option.compare("usrdef")==0)
            {
                if(length!=row*column*channel)
                {
                    throw "Non-matching matrix size!";
                }
                if(data==NULL)
                {
                    this->row=0;
                    this->column=0;
                    this->channel=0;
                    throw "Failed to find the user-defined data!";
                }
                this->data=data;
            }
            else
            {
                throw "Invalid option of construction!";
                this->data=NULL;
            }
        }
        count=new int[sizeof(int)]{1};
    }

    Mat(const Mat & mat):row(mat.row),column(mat.column),channel(mat.channel),data(mat.data)
    {
        mat.count[0]++;
        this->count=mat.count;
    }

    ~Mat()
    {
        count[0]--;
        if(count[0]==0)
        {
            delete [] this->data;
            delete [] count;
            cout<<"Successfully free the memory!"<<endl;
        }
    }

    Mat& operator=(const Mat & mat) 
    {
        if(mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(!(*this==mat))
        {
            mat.count[0]++;
            this->row=mat.row;
            this->column=mat.column;
            this->channel=mat.channel;
            delete [] this->data;
            delete [] this->count;
            this->data=mat.data;
            this->count=mat.count;
        }   
        return *this;
    }

    T operator()(size_t rowidx,size_t colidx,size_t chanidx)
    {
        if(this->data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(rowidx>this->row)
        {
            throw "The row idx is out of bound!";
        }
        if(colidx>this->column)
        {
            throw "The column idx is out of bound!";
        }
        if(chanidx>this->channel)
        {
            throw "The channel idx is out of bound!";
        }
        return this->data[(chanidx-1)*this->row*this->column+(rowidx-1)*this->column+(colidx-1)];
    }

    bool operator==(const Mat & mat)
    {
        if(this->data==NULL||mat.data==NULL)
        {
            return false;
        }
        if(this->row!=mat.row||this->column!=mat.column||this->channel!=mat.channel)
        {
            return false;
        }
        for(size_t idx=0;idx<this->row*this->column*this->channel;idx++)
        {
            if(this->data[idx]!=mat.data[idx])
            {
                return false;
            }
        }
        return true;
    }

    friend ostream & operator<<(ostream & os,const Mat & mat)
    {
        size_t row=mat.row;
        size_t column=mat.column;
        size_t channel=mat.channel;
        if(mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(mat.channel==1)
        {
            if(mat.row==1)
            {
                os<<"[";
                size_t col=0;
                for(;col<mat.column-1;col++)
                {
                    os<<mat.data[col]<<setprecision(4)<<", ";
                }
                os<<mat.data[col]<<setprecision(4)<<"]"<<endl<<endl;
            }
            else
            {
                os<<"[[";
                size_t row=0;
                size_t col=0;
                for(;row<mat.row-1;row++)
                {
                    col=0;
                    for(;col<mat.column-1;col++){
                        os<<mat.data[row*mat.column+col]<<setprecision(4)<<", ";
                    }
                    os<<mat.data[row*mat.column+col]<<setprecision(4)<<"],"<<endl<<" [";
                }
                col=0;
                for(;col<mat.column-1;col++)
                {
                    os<<mat.data[row*mat.column+col]<<setprecision(4)<<", ";
                }
                os<<mat.data[row*mat.column+col]<<setprecision(4)<<"]]"<<endl<<endl;
            }
        }
        else
        {
            if(mat.row==1)
            {
                os<<"[[[";
                size_t col=0;
                size_t chan=0;
                for(;chan<mat.channel-1;chan++)
                {
                    for(;col<(chan+1)*mat.column-1;col++)
                    {
                        os<<mat.data[col]<<setprecision(4)<<", ";
                    }
                    os<<mat.data[col]<<setprecision(4)<<"]],"<<endl<<endl<<" [[";
                    col++;
                }
                for(;col<(chan+1)*mat.column-1;col++)
                {
                    os<<mat.data[col]<<setprecision(4)<<", ";
                }
                os<<mat.data[col]<<setprecision(4)<<"]]]"<<endl<<endl;
            }
            else
            {
                os<<"[[[";
                size_t row=0;
                size_t col=0;
                size_t chan=0;
                for(;chan<mat.channel-1;chan++)
                {
                    row=0;
                    for(;row<mat.row-1;row++)
                    {
                        for(;col<chan*mat.row*mat.column+(row+1)*mat.column-1;col++)
                        {
                            os<<mat.data[col]<<setprecision(4)<<", ";
                        }
                        os<<mat.data[col]<<setprecision(4)<<"],"<<endl<<"  [";
                        col++;
                    }
                    for(;col<chan*mat.row*mat.column+(row+1)*mat.column-1;col++)
                    {
                        os<<mat.data[col]<<setprecision(4)<<", ";
                    }
                    os<<mat.data[col]<<setprecision(4)<<"]],"<<endl<<endl<<" [[";
                    col++;
                }
                row=0;
                for(;row<mat.row-1;row++)
                {
                    for(;col<chan*mat.row*mat.column+(row+1)*mat.column-1;col++)
                    {
                        os<<mat.data[col]<<setprecision(4)<<", ";
                    }
                    os<<mat.data[col]<<setprecision(4)<<"],"<<endl<<"  [";
                    col++;
                }
                for(;col<chan*mat.row*mat.column+(row+1)*mat.column-1;col++)
                {
                    os<<mat.data[col]<<setprecision(4)<<", ";
                }
                os<<mat.data[col]<<setprecision(4)<<"]]]"<<endl<<endl;
            }
        }
        return os;
    }

    Mat operator+(const Mat & mat)
    {
        Mat outcome;
        if(this->data==NULL||mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(this->row!=mat.row)
        {
            throw "Non-matching rows!";
        }
        if(this->column!=mat.column)
        {
            throw "Non-matching columns!";
        }
        if(this->channel!=mat.channel)
        {
            throw "Non-matching channels!";
        }
        outcome.row=this->row;
        outcome.column=this->column;
        outcome.channel=this->channel;
        if(outcome.data==NULL)
        {
            delete [] outcome.data;
        }
        try
        {
        outcome.data=new T[sizeof(T)*mat.row*mat.column*mat.channel];
        }
        catch(bad_alloc & ba)
        {
            cerr<<ba.what()<<endl;
        }
        for(size_t idx=0;idx<this->row*this->column*this->channel;idx++)
        {
            outcome.data[idx]=this->data[idx]+mat.data[idx];
        }
        return outcome;
    }

    Mat operator-(const Mat & mat)
    {
        Mat outcome;
        if(this->data==NULL||mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(this->row!=mat.row)
        {
            throw "Non-matching rows!";
        }
        if(this->column!=mat.column)
        {
            throw "Non-matching columns!";
        }
        if(this->channel!=mat.channel)
        {
            throw "Non-matching channels!";
        }
        outcome.row=this->row;
        outcome.column=this->column;
        outcome.channel=this->channel;
        if(outcome.data==NULL)
        {
            delete [] outcome.data;
        }
        try
        {
        outcome.data=new T[sizeof(T)*mat.row*mat.column*mat.channel];
        }
        catch(bad_alloc & ba)
        {
            cerr<<ba.what()<<endl;
        }
        for(size_t idx=0;idx<this->row*this->column*this->channel;idx++)
        {
            outcome.data[idx]=this->data[idx]-mat.data[idx];
        }
        return outcome;
    }

    Mat operator*(const Mat & mat)
    {
        Mat outcome;
        if(this->data==NULL||mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(this->column!=mat.row)
        {
            throw "Non-matching columns and rows!";
        }
        if(this->channel!=mat.channel)
        {
            throw "Non-matching channels";
        }
        outcome.row=this->row;
        outcome.column=mat.column;
        outcome.channel=this->channel;
        if(outcome.data==NULL)
        {
            delete [] outcome.data;
        }
        try
        {
        outcome.data=new T[sizeof(T)*this->row*mat.column*this->channel];
        }
        catch(bad_alloc & ba)
        {
            cerr<<ba.what()<<endl;
        }
        size_t chan=0;
        size_t row=0;
        size_t col1=0;
        size_t col2=0;
        size_t idx=0;
        T value=0;
        for(;chan<this->channel;chan++)
        {
            for(row=0;row<this->row;row++)
            {
                for(col1=0;col1<mat.column;col1++,idx++)
                {
                    value=0;
                    for(col2=0;col2<this->column;col2++)
                    {
                        value+=this->data[chan*this->row*this->column+row*this->column+col2]*mat.data[chan*mat.row*mat.column+col1+col2*mat.column];
                    }
                    outcome.data[idx]=value;
                }
            }
        }
        return outcome;
    }
};

template<>
class Mat<unsigned>
{
    size_t row;
    size_t column;
    size_t channel;
    unsigned * data;
    int * count;
public:
    Mat(size_t row=0,size_t column=0,size_t channel=0,string option="zeros",unsigned * data=NULL,size_t length=0):row(row),column(column),channel(channel)
    {
        if(this->row==0||this->column==0||this->channel==0)
        {
            this->row=0;
            this->column=0;
            this->channel=0;
            this->data=NULL;
        }
        else
        {
            this->data=new unsigned[sizeof(unsigned)*row*column*channel]{};
            if(option.compare("zeros")==0)
            {
                ;
            }
            else if(option.compare("ones")==0)
            {
                for(size_t idx=0;idx<row*column*channel;idx++)
                {
                    this->data[idx]=1;
                }
            }
            else if(option.compare("rand")==0)
            {
                for(size_t idx=0;idx<row*column*channel;idx++)
                {
                    this->data[idx]=(unsigned)((rand()%1000)/100.0f);
                }
            }
            else if(option.compare("usrdef")==0)
            {
                if(length!=row*column*channel)
                {
                    throw "Non-matching matrix size!";
                }
                if(data==NULL)
                {
                    this->row=0;
                    this->column=0;
                    this->channel=0;
                    throw "Failed to find the user-defined data!";
                }
                this->data=data;
            }
            else
            {
                throw "Invalid option of construction!";
                this->data=NULL;
            }
        }
        count=new int[sizeof(int)]{1};
    }

    Mat(const Mat & mat):row(mat.row),column(mat.column),channel(mat.channel),data(mat.data)
    {
        mat.count[0]++;
        this->count=mat.count;
    }

    ~Mat()
    {
        count[0]--;
        if(count[0]==0)
        {
            delete [] this->data;
            delete [] count;
            cout<<"Successfully free the memory!"<<endl;
        }
    }

    Mat& operator=(const Mat & mat) 
    {
        if(mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(!(*this==mat))
        {
            mat.count[0]++;
            this->row=mat.row;
            this->column=mat.column;
            this->channel=mat.channel;
            delete [] this->data;
            delete [] this->count;
            this->data=mat.data;
            this->count=mat.count;
        }   
        return *this;
    }

    unsigned operator()(size_t rowidx,size_t colidx,size_t chanidx)
    {
        if(this->data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(rowidx>this->row)
        {
            throw "The row idx is out of bound!";
        }
        if(colidx>this->column)
        {
            throw "The column idx is out of bound!";
        }
        if(chanidx>this->channel)
        {
            throw "The channel idx is out of bound!";
        }
        return this->data[(chanidx-1)*this->row*this->column+(rowidx-1)*this->column+(colidx-1)];
    }

    bool operator==(const Mat & mat)
    {
        if(this->data==NULL||mat.data==NULL)
        {
            return false;
        }
        if(this->row!=mat.row||this->column!=mat.column||this->channel!=mat.channel)
        {
            return false;
        }
        for(size_t idx=0;idx<this->row*this->column*this->channel;idx++)
        {
            if(this->data[idx]!=mat.data[idx])
            {
                return false;
            }
        }
        return true;
    }

    friend ostream & operator<<(ostream & os,const Mat & mat)
    {
        size_t row=mat.row;
        size_t column=mat.column;
        size_t channel=mat.channel;
        if(mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(mat.channel==1)
        {
            if(mat.row==1)
            {
                os<<"[";
                size_t col=0;
                for(;col<mat.column-1;col++)
                {
                    os<<mat.data[col]<<setprecision(4)<<", ";
                }
                os<<mat.data[col]<<setprecision(4)<<"]"<<endl<<endl;
            }
            else
            {
                os<<"[[";
                size_t row=0;
                size_t col=0;
                for(;row<mat.row-1;row++)
                {
                    col=0;
                    for(;col<mat.column-1;col++){
                        os<<mat.data[row*mat.column+col]<<setprecision(4)<<", ";
                    }
                    os<<mat.data[row*mat.column+col]<<setprecision(4)<<"],"<<endl<<" [";
                }
                col=0;
                for(;col<mat.column-1;col++)
                {
                    os<<mat.data[row*mat.column+col]<<setprecision(4)<<", ";
                }
                os<<mat.data[row*mat.column+col]<<setprecision(4)<<"]]"<<endl<<endl;
            }
        }
        else
        {
            if(mat.row==1)
            {
                os<<"[[[";
                size_t col=0;
                size_t chan=0;
                for(;chan<mat.channel-1;chan++)
                {
                    for(;col<(chan+1)*mat.column-1;col++)
                    {
                        os<<mat.data[col]<<setprecision(4)<<", ";
                    }
                    os<<mat.data[col]<<setprecision(4)<<"]],"<<endl<<endl<<" [[";
                    col++;
                }
                for(;col<(chan+1)*mat.column-1;col++)
                {
                    os<<mat.data[col]<<setprecision(4)<<", ";
                }
                os<<mat.data[col]<<setprecision(4)<<"]]]"<<endl<<endl;
            }
            else
            {
                os<<"[[[";
                size_t row=0;
                size_t col=0;
                size_t chan=0;
                for(;chan<mat.channel-1;chan++)
                {
                    row=0;
                    for(;row<mat.row-1;row++)
                    {
                        for(;col<chan*mat.row*mat.column+(row+1)*mat.column-1;col++)
                        {
                            os<<mat.data[col]<<setprecision(4)<<", ";
                        }
                        os<<mat.data[col]<<setprecision(4)<<"],"<<endl<<"  [";
                        col++;
                    }
                    for(;col<chan*mat.row*mat.column+(row+1)*mat.column-1;col++)
                    {
                        os<<mat.data[col]<<setprecision(4)<<", ";
                    }
                    os<<mat.data[col]<<setprecision(4)<<"]],"<<endl<<endl<<" [[";
                    col++;
                }
                row=0;
                for(;row<mat.row-1;row++)
                {
                    for(;col<chan*mat.row*mat.column+(row+1)*mat.column-1;col++)
                    {
                        os<<mat.data[col]<<setprecision(4)<<", ";
                    }
                    os<<mat.data[col]<<setprecision(4)<<"],"<<endl<<"  [";
                    col++;
                }
                for(;col<chan*mat.row*mat.column+(row+1)*mat.column-1;col++)
                {
                    os<<mat.data[col]<<setprecision(4)<<", ";
                }
                os<<mat.data[col]<<setprecision(4)<<"]]]"<<endl<<endl;
            }
        }
        return os;
    }

    Mat operator+(const Mat & mat)
    {
        Mat outcome;
        if(this->data==NULL||mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(this->row!=mat.row)
        {
            throw "Non-matching rows!";
        }
        if(this->column!=mat.column)
        {
            throw "Non-matching columns!";
        }
        if(this->channel!=mat.channel)
        {
            throw "Non-matching channels!";
        }
        outcome.row=this->row;
        outcome.column=this->column;
        outcome.channel=this->channel;
        if(outcome.data==NULL)
        {
            delete [] outcome.data;
        }
        try
        {
        outcome.data=new unsigned[sizeof(unsigned)*mat.row*mat.column*mat.channel];
        }
        catch(bad_alloc & ba)
        {
            cerr<<ba.what()<<endl;
        }
        for(size_t idx=0;idx<this->row*this->column*this->channel;idx++)
        {
            outcome.data[idx]=this->data[idx]+mat.data[idx];
        }
        return outcome;
    }

    Mat operator-(const Mat & mat)
    {
        Mat outcome;
        if(this->data==NULL||mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(this->row!=mat.row)
        {
            throw "Non-matching rows!";
        }
        if(this->column!=mat.column)
        {
            throw "Non-matching columns!";
        }
        if(this->channel!=mat.channel)
        {
            throw "Non-matching channels!";
        }
        outcome.row=this->row;
        outcome.column=this->column;
        outcome.channel=this->channel;
        if(outcome.data==NULL)
        {
            delete [] outcome.data;
        }
        try
        {
        outcome.data=new unsigned[sizeof(unsigned)*mat.row*mat.column*mat.channel];
        }
        catch(bad_alloc & ba)
        {
            cerr<<ba.what()<<endl;
        }
        for(size_t idx=0;idx<this->row*this->column*this->channel;idx++)
        {
            if(this->data[idx]<mat.data[idx])
            {
                throw "The subtracted value is less than zero, which may cause unexpected problems!";
            }
            else
            {
                outcome.data[idx]=this->data[idx]-mat.data[idx];
            }
        }
        return outcome;
    }

    Mat operator*(const Mat & mat)
    {
        Mat outcome;
        if(this->data==NULL||mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(this->column!=mat.row)
        {
            throw "Non-matching columns and rows!";
        }
        if(this->channel!=mat.channel)
        {
            throw "Non-matching channels";
        }
        outcome.row=this->row;
        outcome.column=mat.column;
        outcome.channel=this->channel;
        if(outcome.data==NULL)
        {
            delete [] outcome.data;
        }
        try
        {
        outcome.data=new unsigned[sizeof(unsigned)*this->row*mat.column*this->channel];
        }
        catch(bad_alloc & ba)
        {
            cerr<<ba.what()<<endl;
        }
        size_t chan=0;
        size_t row=0;
        size_t col1=0;
        size_t col2=0;
        size_t idx=0;
        unsigned value=0;
        for(;chan<this->channel;chan++)
        {
            for(row=0;row<this->row;row++)
            {
                for(col1=0;col1<mat.column;col1++,idx++)
                {
                    value=0;
                    for(col2=0;col2<this->column;col2++)
                    {
                        value+=this->data[chan*this->row*this->column+row*this->column+col2]*mat.data[chan*mat.row*mat.column+col1+col2*mat.column];
                    }
                    outcome.data[idx]=value;
                }
            }
        }
        return outcome;
    }
};

template<>
class Mat<char>
{
    size_t row;
    size_t column;
    size_t channel;
    char * data;
    int * count;
public:
    Mat(size_t row=0,size_t column=0,size_t channel=0,string option="zeros",char * data=NULL,size_t length=0):row(row),column(column),channel(channel)
    {
        if(this->row==0||this->column==0||this->channel==0)
        {
            this->row=0;
            this->column=0;
            this->channel=0;
            this->data=NULL;
        }
        else
        {
            this->data=new char[sizeof(char)*row*column*channel];
            if(option.compare("zeros")==0)
            {
                for(size_t idx=0;idx<row*column*channel;idx++)
                {
                    this->data[idx]='0';
                }
            }
            else if(option.compare("ones")==0)
            {
                for(size_t idx=0;idx<row*column*channel;idx++)
                {
                    this->data[idx]='1';
                }
            }
            else if(option.compare("rand")==0)
            {
                for(size_t idx=0;idx<row*column*channel;idx++)
                {
                    this->data[idx]=(rand()%10)+'0';
                }
            }
            else if(option.compare("usrdef")==0)
            {
                if(length!=row*column*channel)
                {
                    throw "Non-matching matrix size!";
                }
                if(data==NULL)
                {
                    this->row=0;
                    this->column=0;
                    this->channel=0;
                    throw "Failed to find the user-defined data!";
                }
                for(size_t idx=0;idx<length;idx++)
                {
                    if(!isdigit(data[idx]))
                    {
                        throw "User-defined matrix data contains nonnumerical values";
                    }
                }
                this->data=data;
            }
            else
            {
                throw "Invalid option of construction!";
                this->data=NULL;
            }
        }
        count=new int[sizeof(int)]{1};
    }

    Mat(const Mat & mat):row(mat.row),column(mat.column),channel(mat.channel),data(mat.data)
    {
        mat.count[0]++;
        this->count=mat.count;
    }

    ~Mat()
    {
        count[0]--;
        if(count[0]==0)
        {
            delete [] this->data;
            delete [] count;
            cout<<"Successfully free the memory!"<<endl;
        }
    }

    Mat& operator=(const Mat & mat) 
    {
        if(mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(!(*this==mat))
        {
            mat.count[0]++;
            this->row=mat.row;
            this->column=mat.column;
            this->channel=mat.channel;
            delete [] this->data;
            delete [] this->count;
            this->data=mat.data;
            this->count=mat.count;
        }   
        return *this;
    }

    char operator()(size_t rowidx,size_t colidx,size_t chanidx)
    {
        if(this->data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(rowidx>this->row)
        {
            throw "The row idx is out of bound!";
        }
        if(colidx>this->column)
        {
            throw "The column idx is out of bound!";
        }
        if(chanidx>this->channel)
        {
            throw "The channel idx is out of bound!";
        }
        return this->data[(chanidx-1)*this->row*this->column+(rowidx-1)*this->column+(colidx-1)];
    }

    bool operator==(const Mat & mat)
    {
        if(this->data==NULL||mat.data==NULL)
        {
            return false;
        }
        if(this->row!=mat.row||this->column!=mat.column||this->channel!=mat.channel)
        {
            return false;
        }
        for(size_t idx=0;idx<this->row*this->column*this->channel;idx++)
        {
            if(this->data[idx]!=mat.data[idx])
            {
                return false;
            }
        }
        return true;
    }

    friend ostream & operator<<(ostream & os,const Mat & mat)
    {
        size_t row=mat.row;
        size_t column=mat.column;
        size_t channel=mat.channel;
        if(mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(mat.channel==1)
        {
            if(mat.row==1)
            {
                os<<"[";
                size_t col=0;
                for(;col<mat.column-1;col++)
                {
                    os<<mat.data[col]<<setprecision(4)<<", ";
                }
                os<<mat.data[col]<<setprecision(4)<<"]"<<endl<<endl;
            }
            else
            {
                os<<"[[";
                size_t row=0;
                size_t col=0;
                for(;row<mat.row-1;row++)
                {
                    col=0;
                    for(;col<mat.column-1;col++){
                        os<<mat.data[row*mat.column+col]<<setprecision(4)<<", ";
                    }
                    os<<mat.data[row*mat.column+col]<<setprecision(4)<<"],"<<endl<<" [";
                }
                col=0;
                for(;col<mat.column-1;col++)
                {
                    os<<mat.data[row*mat.column+col]<<setprecision(4)<<", ";
                }
                os<<mat.data[row*mat.column+col]<<setprecision(4)<<"]]"<<endl<<endl;
            }
        }
        else
        {
            if(mat.row==1)
            {
                os<<"[[[";
                size_t col=0;
                size_t chan=0;
                for(;chan<mat.channel-1;chan++)
                {
                    for(;col<(chan+1)*mat.column-1;col++)
                    {
                        os<<mat.data[col]<<setprecision(4)<<", ";
                    }
                    os<<mat.data[col]<<setprecision(4)<<"]],"<<endl<<endl<<" [[";
                    col++;
                }
                for(;col<(chan+1)*mat.column-1;col++)
                {
                    os<<mat.data[col]<<setprecision(4)<<", ";
                }
                os<<mat.data[col]<<setprecision(4)<<"]]]"<<endl<<endl;
            }
            else
            {
                os<<"[[[";
                size_t row=0;
                size_t col=0;
                size_t chan=0;
                for(;chan<mat.channel-1;chan++)
                {
                    row=0;
                    for(;row<mat.row-1;row++)
                    {
                        for(;col<chan*mat.row*mat.column+(row+1)*mat.column-1;col++)
                        {
                            os<<mat.data[col]<<setprecision(4)<<", ";
                        }
                        os<<mat.data[col]<<setprecision(4)<<"],"<<endl<<"  [";
                        col++;
                    }
                    for(;col<chan*mat.row*mat.column+(row+1)*mat.column-1;col++)
                    {
                        os<<mat.data[col]<<setprecision(4)<<", ";
                    }
                    os<<mat.data[col]<<setprecision(4)<<"]],"<<endl<<endl<<" [[";
                    col++;
                }
                row=0;
                for(;row<mat.row-1;row++)
                {
                    for(;col<chan*mat.row*mat.column+(row+1)*mat.column-1;col++)
                    {
                        os<<mat.data[col]<<setprecision(4)<<", ";
                    }
                    os<<mat.data[col]<<setprecision(4)<<"],"<<endl<<"  [";
                    col++;
                }
                for(;col<chan*mat.row*mat.column+(row+1)*mat.column-1;col++)
                {
                    os<<mat.data[col]<<setprecision(4)<<", ";
                }
                os<<mat.data[col]<<setprecision(4)<<"]]]"<<endl<<endl;
            }
        }
        return os;
    }

    Mat operator+(const Mat & mat)
    {
        Mat outcome;
        if(this->data==NULL||mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(this->row!=mat.row)
        {
            throw "Non-matching rows!";
        }
        if(this->column!=mat.column)
        {
            throw "Non-matching columns!";
        }
        if(this->channel!=mat.channel)
        {
            throw "Non-matching channels!";
        }
        outcome.row=this->row;
        outcome.column=this->column;
        outcome.channel=this->channel;
        if(outcome.data==NULL)
        {
            delete [] outcome.data;
        }
        try
        {
        outcome.data=new char[sizeof(char)*mat.row*mat.column*mat.channel];
        }
        catch(bad_alloc & ba)
        {
            cerr<<ba.what()<<endl;
        }
        for(size_t idx=0;idx<this->row*this->column*this->channel;idx++)
        {
            int result=(this->data[idx]-'0')+(mat.data[idx]-'0');
            if(result>=10)
            {
                throw "The added value is greater than nine, which may cause unexpected problems!";
            }
            outcome.data[idx]=result+'0';
        }
        return outcome;
    }

    Mat operator-(const Mat & mat)
    {
        Mat outcome;
        if(this->data==NULL||mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(this->row!=mat.row)
        {
            throw "Non-matching rows!";
        }
        if(this->column!=mat.column)
        {
            throw "Non-matching columns!";
        }
        if(this->channel!=mat.channel)
        {
            throw "Non-matching channels!";
        }
        outcome.row=this->row;
        outcome.column=this->column;
        outcome.channel=this->channel;
        if(outcome.data==NULL)
        {
            delete [] outcome.data;
        }
        try
        {
        outcome.data=new char[sizeof(char)*mat.row*mat.column*mat.channel];
        }
        catch(bad_alloc & ba)
        {
            cerr<<ba.what()<<endl;
        }
        for(size_t idx=0;idx<this->row*this->column*this->channel;idx++)
        {
            int result=(this->data[idx]-'0')-(mat.data[idx]-'0');
            if(result<0)
            {
                throw "The subtracted value is less than zero, which may cause unexpected problems!";
            }
            outcome.data[idx]=result+'0';
        }
        return outcome;
    }

    Mat operator*(const Mat & mat)
    {
        Mat outcome;
        if(this->data==NULL||mat.data==NULL)
        {
            throw "Empty matrix data!";
        }
        if(this->column!=mat.row)
        {
            throw "Non-matching columns and rows!";
        }
        if(this->channel!=mat.channel)
        {
            throw "Non-matching channels";
        }
        outcome.row=this->row;
        outcome.column=mat.column;
        outcome.channel=this->channel;
        if(outcome.data==NULL)
        {
            delete [] outcome.data;
        }
        try
        {
        outcome.data=new char[sizeof(char)*this->row*mat.column*this->channel];
        }
        catch(bad_alloc & ba)
        {
            cerr<<ba.what()<<endl;
        }
        size_t chan=0;
        size_t row=0;
        size_t col1=0;
        size_t col2=0;
        size_t idx=0;
        int value=0;
        for(;chan<this->channel;chan++)
        {
            for(row=0;row<this->row;row++)
            {
                for(col1=0;col1<mat.column;col1++,idx++)
                {
                    value=0;
                    for(col2=0;col2<this->column;col2++)
                    {
                        value+=(this->data[chan*this->row*this->column+row*this->column+col2]-'0')*(mat.data[chan*mat.row*mat.column+col1+col2*mat.column]-'0');
                    }
                    if(value>9)
                    {
                        throw "The multiplied value is greater than nine, which may cause unexpected problems!";
                    }
                    outcome.data[idx]=value+'0';
                }
            }
        }
        return outcome;
    }
};

template class Mat<unsigned>;
template class Mat<char>;
template class Mat<short>;
template class Mat<int>;
template class Mat<float>;
template class Mat<double>;
#endif
