#include "header.hpp"
#include <iostream>
using namespace std;

int main()
{
    try
    {
        srand(time(0));
        float * mptr=new float[sizeof(float)*8]{12.12f,7.41f,8.57f,-1.36f,0.00f,-9.24f,4.58f};
        Mat<float> mat1(2,2,2,"usrdef",mptr,8);
        Mat<float> mat2(2,2,2,"rand");
        Mat<float> mat3=(mat1*mat2);
        cout<<mat1<<mat2<<mat3<<endl;
    }
    catch(const char * error)
    {
        cerr<<error<<endl;
    }
    return 0;
}
