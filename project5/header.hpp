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
public:
    Mat(size_t row=0,size_t column=0,size_t channel=0,string option="zeros"):row(row),column(column),channel(channel)
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
            else
            {
                cerr<<"Invalid option!"<<endl;
            }
        }
    }
    ~Mat()
    {
        delete [] this->data;
    }

    Mat& operator=(const Mat& mat) 
    {
        if(mat.data==NULL)
        {
            cerr<<"The assigned data is empty!"<<endl;
            return *this;
        }
        this->row=mat.row;
        this->column=mat.column;
        this->channel=mat.channel;
        if(this->data==NULL)
        {
            delete [] this->data;
            this->data=new T[sizeof(T)*this->row*this->column*this->channel]{};
        }
        void * p=memcpy(this->data,mat.data,sizeof(T)*this->row*this->column*this->channel);
        if(this->data==NULL)
        {
            cerr<<"The assignment operation failed!"<<endl;
        }
        return *this;
    }

    T operator()(size_t rowidx,size_t colidx,size_t chanidx)
    {
        if(this->data==NULL)
        {
            cerr<<"The data of matrix is empty!"<<endl;
            return 0;
        }
        if(rowidx>this->row)
        {
            cerr<<"The row idx is out of bound!"<<endl;
            return 0;
        }
        if(colidx>this->column)
        {
            cerr<<"The column idx is out of bound!"<<endl;
            return 0;
        }
        if(chanidx>this->channel)
        {
            cerr<<"The channel idx is out of bound!"<<endl;
            return 0;
        }
        return this->data[(chanidx-1)*this->row*this->column+(rowidx-1)*this->column+(colidx-1)];
    }

    bool operator==(const Mat & mat)
    {
        if(this->data==NULL||mat.data==NULL)
        {
            cerr<<"The compared matrix has empty data!"<<endl;
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
            cerr<<"Failed to print the empty data!"<<endl;
            return os;
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

    Mat operator+(T scalar)
    {
        Mat outcome;
        if(this->data==NULL)
        {
            cerr<<"The data of the matrix is empty!"<<endl;
            return outcome;
        }
        outcome.row=this->row;
        outcome.column=this->column;
        outcome.channel=this->channel;
        delete [] outcome.data;
        outcome.data=new T[sizeof(T)*this->row*this->column*this->channel];
        if(outcome.data==NULL)
        {
            cerr<<"Failed to allocate memory for the matrix data!"<<endl;
            return outcome;
        }
        for(size_t idx=0;idx<outcome.row*outcome.column*outcome.channel;idx++)
        {
            outcome.data[idx]=this->data[idx]+scalar;
        }
        return outcome;
    }
    
    friend Mat operator+(T scalar,const Mat & mat)
    {
        Mat outcome;
        if(mat.data==NULL)
        {
            cerr<<"The data of the matrix is empty!"<<endl;
            return outcome;
        }
        outcome.row=mat.row;
        outcome.column=mat.column;
        outcome.channel=mat.channel;
        delete [] outcome.data;
        outcome.data=new T[sizeof(T)*mat.row*mat.column*mat.channel];
        if(outcome.data==NULL)
        {
            cerr<<"Failed to allocate memory for the matrix data!"<<endl;
            return outcome;
        }
        for(size_t idx=0;idx<outcome.row*outcome.column*outcome.channel;idx++)
        {
            outcome.data[idx]=scalar+mat.data[idx];
        }
        return outcome;
    }

    Mat operator+(const Mat & mat)
    {
        Mat outcome;
        if(this->data==NULL||mat.data==NULL)
        {
            cerr<<"The data of the adding matrix is empty!"<<endl;
            return outcome;
        }
        if(this->row!=mat.row)
        {
            cerr<<"Invalid row!"<<endl;
            return outcome;
        }
        if(this->column!=mat.column)
        {
            cerr<<"Invalid column!"<<endl;
            return outcome;
        }
        if(this->channel!=mat.channel)
        {
            cerr<<"Invalid channel!"<<endl;
            return outcome;
        }
        outcome.row=this->row;
        outcome.column=this->column;
        outcome.channel=this->channel;
        delete [] outcome.data;
        outcome.data=new T[sizeof(T)*mat.row*mat.column*mat.channel];
        if(outcome.data==NULL)
        {
            cerr<<"Failed to allocate memory for the matrix data!"<<endl;
            return outcome;
        }
        for(size_t idx=0;idx<this->row*this->column*this->channel;idx++)
        {
            outcome.data[idx]=this->data[idx]+mat.data[idx];
        }
        return outcome;
    }

    Mat operator-(T scalar)
    {
        Mat outcome;
        if(this->data==NULL)
        {
            cerr<<"The data of the matrix is empty!"<<endl;
            return outcome;
        }
        outcome.row=this->row;
        outcome.column=this->column;
        outcome.channel=this->channel;
        delete [] outcome.data;
        outcome.data=new T[sizeof(T)*this->row*this->column*this->channel];
        if(outcome.data==NULL)
        {
            cerr<<"Failed to allocate memory for the matrix data!"<<endl;
            return outcome;
        }
        for(size_t idx=0;idx<outcome.row*outcome.column*outcome.channel;idx++)
        {
            outcome.data[idx]=this->data[idx]-scalar;
        }
        return outcome;
    }
    
    friend Mat operator-(T scalar,const Mat & mat)
    {
        Mat outcome;
        if(mat.data==NULL)
        {
            cerr<<"The data of the matrix is empty!"<<endl;
            return outcome;
        }
        outcome.row=mat.row;
        outcome.column=mat.column;
        outcome.channel=mat.channel;
        delete [] outcome.data;
        outcome.data=new T[sizeof(T)*mat.row*mat.column*mat.channel];
        if(outcome.data==NULL)
        {
            cerr<<"Failed to allocate memory for the matrix data!"<<endl;
            return outcome;
        }
        for(size_t idx=0;idx<outcome.row*outcome.column*outcome.channel;idx++)
        {
            outcome.data[idx]=scalar-mat.data[idx];
        }
        return outcome;
    }

    Mat operator-(const Mat & mat)
    {
        Mat outcome;
        if(this->data==NULL||mat.data==NULL)
        {
            cerr<<"The data of the subtracting matrix is empty!"<<endl;
            return outcome;
        }
        if(this->row!=mat.row)
        {
            cerr<<"Invalid row!"<<endl;
            return outcome;
        }
        if(this->column!=mat.column)
        {
            cerr<<"Invalid column!"<<endl;
            return outcome;
        }
        if(this->channel!=mat.channel)
        {
            cerr<<"Invalid channel!"<<endl;
            return outcome;
        }
        outcome.row=this->row;
        outcome.column=this->column;
        outcome.channel=this->channel;
        delete [] outcome.data;
        outcome.data=new T[sizeof(T)*mat.row*mat.column*mat.channel];
        if(outcome.data==NULL)
        {
            cerr<<"Failed to allocate memory for the matrix data!"<<endl;
            return outcome;
        }
        for(size_t idx=0;idx<this->row*this->column*this->channel;idx++)
        {
            outcome.data[idx]=this->data[idx]-mat.data[idx];
        }
        return outcome;
    }

    Mat operator*(T scalar)
    {
        Mat outcome;
        if(this->data==NULL)
        {
            cerr<<"The data of the matrix is empty!"<<endl;
            return outcome;
        }
        outcome.row=this->row;
        outcome.column=this->column;
        outcome.channel=this->channel;
        delete [] outcome.data;
        outcome.data=new T[sizeof(T)*this->row*this->column*this->channel];
        if(outcome.data==NULL)
        {
            cerr<<"Failed to allocate memory for the matrix data!"<<endl;
            return outcome;
        }
        for(size_t idx=0;idx<outcome.row*outcome.column*outcome.channel;idx++)
        {
            outcome.data[idx]=this->data[idx]*scalar;
        }
        return outcome;
    }

    friend Mat operator*(T scalar,const Mat & mat)
    {
        Mat outcome;
        if(mat.data==NULL)
        {
            cerr<<"The data of the matrix is empty!"<<endl;
            return outcome;
        }
        outcome.row=mat.row;
        outcome.column=mat.column;
        outcome.channel=mat.channel;
        delete [] outcome.data;
        outcome.data=new T[sizeof(T)*mat.row*mat.column*mat.channel];
        if(outcome.data==NULL)
        {
            cerr<<"Failed to allocate memory for the matrix data!"<<endl;
            return outcome;
        }
        for(size_t idx=0;idx<outcome.row*outcome.column*outcome.channel;idx++)
        {
            outcome.data[idx]=mat.data[idx]*scalar;
        }
        return outcome;
    }

    Mat operator*(const Mat & mat)
    {
        Mat outcome;
        if(this->data==NULL||mat.data==NULL)
        {
            cerr<<"The data of the multiplying matrix is empty!"<<endl;
            return outcome;
        }
        if(this->column!=mat.row)
        {
            cerr<<"Non-matching columns and rows!"<<endl;
            return outcome;
        }
        if(this->channel!=mat.channel)
        {
            cerr<<"Invalid channel!"<<endl;
            return outcome;
        }
        outcome.row=this->row;
        outcome.column=mat.column;
        outcome.channel=this->channel;
        delete [] outcome.data;
        outcome.data=new T[sizeof(T)*this->row*mat.column*this->channel];
        if(outcome.data==NULL)
        {
            cerr<<"Failed to allocate memory for the matrix data!"<<endl;
            return outcome;
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

template class Mat<unsigned>;
template class Mat<char>;
template class Mat<short>;
template class Mat<int>;
template class Mat<float>;
template class Mat<double>;
#endif



