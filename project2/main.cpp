#include <iostream>
#include "function.cpp"
#include <string>
using namespace std;

int main(){
    string str;
    string* variables=new string[20];  //存储变量
    string* values=new string[20];     //存储变量对应的值
    int i=0;
    cin>>str;
    while(str.find('=')!=string::npos){
        variables[i]=str.substr(0,str.find('='));
        values[i]=str.substr(str.find('=')+1);
        i++;
        cin>>str;
    }
    for(int j=0;j<i;j++){
        str=str.replace(str.find(variables[j]),variables[j].size(),values[j]);
    }
    cout<<CPU(str)<<endl;
    return 0;
}
