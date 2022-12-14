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
    
    bool printMatrix();

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

    // Mat * operator+(const Mat & mat)
    // {
    //     Mat * matptr=new Mat[sizeof(Mat)];
    //     if(matptr==NULL)
    //     {
    //         cerr<<"Failed to allocate memory for the matrix pointer!"<<endl;
    //         return NULL;
    //     }
    //     if(this->data==NULL||mat.data==NULL)
    //     {
    //         cerr<<"The data of the matrix is empty!"<<endl;
    //         return NULL;
    //     }
    //     if(this->row!=mat.row)
    //     {
    //         cerr<<"Invalid row!"<<endl;
    //         return NULL;
    //     }
    //     if(this->column!=mat.column)
    //     {
    //         cerr<<"Invalid column!"<<endl;
    //         return NULL;
    //     }
    //     if(this->channel!=mat.channel)
    //     {
    //         cerr<<"Invalid channel!"<<endl;
    //         return NULL;
    //     }
    //     matptr->row=this->row;
    //     matptr->column=this->column;
    //     matptr->channel=this->channel;
    //     matptr->data=new T[sizeof(T)*mat.row*mat.column*mat.channel];
    //     if(matptr->data==NULL)
    //     {
    //         cerr<<"Failed to allocate memory for the matrix data!"<<endl;
    //         return NULL;
    //     }
    //     for(size_t idx=0;idx<this->row*this->column*this->channel;idx++)
    //     {
    //         matptr->data[idx]=this->data[idx]+mat.data[idx];
    //     }
    //     return matptr;
    // }
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

template<typename T>
bool Mat<T>::printMatrix()
{
    size_t row=this->row;
    size_t column=this->column;
    size_t channel=this->channel;
    if(this->data==NULL)
    {
        cerr<<"Failed to print the empty data!"<<endl;
        return false;
    }
    if(this->channel==1)
    {
        if(this->row==1)
        {
            cout<<"[";
            size_t col=0;
            for(;col<this->column-1;col++)
            {
                cout<<this->data[col]<<setprecision(4)<<", ";
            }
            cout<<this->data[col]<<setprecision(4)<<"]"<<endl<<endl;
        }
        else
        {
            cout<<"[[";
            size_t row=0;
            size_t col=0;
            for(;row<this->row-1;row++)
            {
                col=0;
                for(;col<this->column-1;col++){
                    cout<<this->data[row*this->column+col]<<setprecision(4)<<", ";
                }
                cout<<this->data[row*this->column+col]<<setprecision(4)<<"],"<<endl<<" [";
            }
            col=0;
            for(;col<this->column-1;col++)
            {
                cout<<this->data[row*this->column+col]<<setprecision(4)<<", ";
            }
            cout<<this->data[row*this->column+col]<<setprecision(4)<<"]]"<<endl<<endl;
        }
    }
    else
    {
        if(this->row==1)
        {
            cout<<"[[[";
            size_t col=0;
            size_t chan=0;
            for(;chan<this->channel-1;chan++)
            {
                for(;col<(chan+1)*this->column-1;col++)
                {
                    cout<<this->data[col]<<setprecision(4)<<", ";
                }
                cout<<this->data[col]<<setprecision(4)<<"]],"<<endl<<endl<<" [[";
                col++;
            }
            for(;col<(chan+1)*this->column-1;col++)
            {
                cout<<this->data[col]<<setprecision(4)<<", ";
            }
            cout<<this->data[col]<<setprecision(4)<<"]]]"<<endl<<endl;
        }
        else
        {
            cout<<"[[[";
            size_t row=0;
            size_t col=0;
            size_t chan=0;
            for(;chan<this->channel-1;chan++)
            {
                row=0;
                for(;row<this->row-1;row++)
                {
                    for(;col<chan*this->row*this->column+(row+1)*this->column-1;col++)
                    {
                        cout<<this->data[col]<<setprecision(4)<<", ";
                    }
                    cout<<this->data[col]<<setprecision(4)<<"],"<<endl<<"  [";
                    col++;
                }
                for(;col<chan*this->row*this->column+(row+1)*this->column-1;col++)
                {
                    cout<<this->data[col]<<setprecision(4)<<", ";
                }
                cout<<this->data[col]<<setprecision(4)<<"]],"<<endl<<endl<<" [[";
                col++;
            }
            row=0;
            for(;row<this->row-1;row++)
            {
                for(;col<chan*this->row*this->column+(row+1)*this->column-1;col++)
                {
                    cout<<this->data[col]<<setprecision(4)<<", ";
                }
                cout<<this->data[col]<<setprecision(4)<<"],"<<endl<<"  [";
                col++;
            }
            for(;col<chan*this->row*this->column+(row+1)*this->column-1;col++)
            {
                cout<<this->data[col]<<setprecision(4)<<", ";
            }
            cout<<this->data[col]<<setprecision(4)<<"]]]"<<endl<<endl;
        }
    }
    return true;
}

template class Mat<unsigned>;
template class Mat<char>;
template class Mat<short>;
template class Mat<int>;
template class Mat<float>;
template class Mat<double>;
#endif
