#include "header.hpp"
#include <iostream>
using namespace std;

int main()
{
    try
    {
        srand(time(0));
        /* Test case #1 */ 
        float * mptr=new float[sizeof(float)*8]{12.12f,7.41f,8.57f,-1.36f,0.00f,-9.24f,4.58f};
        Mat<float> mat1(2,2,2,"usrdef",mptr,8);
        Mat<float> mat2(2,2,2,"rand");
        Mat<float> mat3=(mat1*mat2);
        Mat<float> mat4;
        mat4=mat3;
        cout<<mat1<<mat2<<mat3<<mat4;
        
        /* Test case #2 */ 
        Mat<char> mat5(2,2,2,"ones");
        Mat<char> mat6(2,2,2,"rand");
        Mat<char> mat7;
        mat7=(mat5*mat6);
        cout<<mat5<<mat6<<mat7;

        /* Test case #3 */ 
        Mat<unsigned> mat8(3,4,3);
        Mat<unsigned> mat9(3,4,3,"ones");
        Mat<unsigned> mat10=(mat8-mat9);
        cout<<mat8<<mat9<<mat10;

        /* Test case #4 */ 
        Mat<int> mat11(5,2,3,"rand");
        Mat<int> mat12(mat11);
        Mat<int> mat13=mat12;
        Mat<int> mat14(2,3,1,"usrdef",NULL,6);
        Mat<int> mat15=mat14;
        cout<<mat11<<mat12<<mat13<<mat14<<mat15;
    }
    catch(const char * error)
    {
        cerr<<error<<endl;
    }
    return 0;
}
