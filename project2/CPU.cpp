#include <iostream>
#include "function.cpp"
#include <string>
using namespace std;



string handler4(string str){
    while(str.find('*')!=string::npos||str.find('/')!=string::npos){
        for(int i=0;i<str.size();i++){
            if(str[i]=='*'||str[i]=='/'){
                int j=i;
                do{
                    j--;
                }while(str[j]!='+'&&str[j]!='-'&&str[j]!='*'&&str[j]!='/'&&j>0);
                string num1;
                if(j==0){
                    num1=str.substr(0,i-j);
                }
                else{
                    num1=str.substr(j+1,i-j-1);
                }
                int k=i;
                do{
                    k++;
                }while(str[k]!='+'&&str[k]!='-'&&str[k]!='*'&&str[k]!='/'&&k<str.size());
                string num2=str.substr(i+1,k-i-1);
                if(j==0){
                    str=str.replace(0,k-j,calculator(subCPU(num1),subCPU(num2),str[i]));
                }
                else{
                    str=str.replace(j+1,k-j-1,calculator(subCPU(num1),subCPU(num2),str[i]));
                }
                break;
            }
        }
    }
    while(str.find('+')!=string::npos||str.find('-')!=string::npos){
        for(int i=0;i<str.size();i++){
            if(str[i]=='+'||str[i]=='-'){
                int j=i;
                do{
                    j--;
                }while(str[j]!='+'&&str[j]!='-'&&str[j]!='*'&&str[j]!='/'&&j>0);
                string num1;
                if(j==0){
                    num1=str.substr(0,i-j);
                }
                else{
                    num1=str.substr(j+1,i-j-1);
                }
                int k=i;
                do{
                    k++;
                }while(str[k]!='+'&&str[k]!='-'&&str[k]!='*'&&str[k]!='/'&&k<str.size());
                string num2=str.substr(i+1,k-i-1);
                if(j==0){
                    str=str.replace(0,k-j,calculator(subCPU(num1),subCPU(num2),str[i]));
                }
                else{
                    str=str.replace(j+1,k-j-1,calculator(subCPU(num1),subCPU(num2),str[i]));
                }
                break;
            }
        }
    }
    
    return str;
}

string CPU(string str){
    while(str.find('[')!=string::npos||str.find('(')!=string::npos||str.find('{')!=string::npos){ //不停循环直到去掉所有的括号和数学方法
        if (str.find('[')!=string::npos){  //有[]
            string str1=str.substr(str.find('[')+1,str.find(']')-str.find('[')-1);
            str=str.replace(str.find('['),str.find(']')-str.find('[')+1,CPU(str1));  
        }
        else{  //没有[],但有()或{}
            if(str.find("max{")!=string::npos){
                string str1=str.substr(str.find('{')+1,str.find(',')-str.find('{')-1);
                string str2=str.substr(str.find(',')+1,str.find('}')-str.find(',')-1);
                str=str.replace(str.find("max{"),str.find('}')-str.find("max{")+1,calculator(subCPU(str1),subCPU(str2),'x'));
            }
            else if(str.find("min{")!=string::npos){
                string str1=str.substr(str.find('{')+1,str.find(',')-str.find('{')-1);
                string str2=str.substr(str.find(',')+1,str.find('}')-str.find(',')-1);
                str=str.replace(str.find("min{"),str.find('}')-str.find("min{")+1,calculator(subCPU(str1),subCPU(str2),'n'));
            }
            else if(str.find("pow{")!=string::npos){
                string str1=str.substr(str.find('{')+1,str.find(',')-str.find('{')-1);
                string str2=str.substr(str.find(',')+1,str.find('}')-str.find(',')-1);
                str=str.replace(str.find("pow{"),str.find('}')-str.find("pow{")+1,calculator(subCPU(str1),subCPU(str2),'w'));
            }
            else{   //加减乘除
                string str1=str.substr(str.find('(')+1,str.find(')')-str.find('(')-1);
                str=str.replace(str.find('('),str.find(')')-str.find('(')+1,handler4(str1));

            }
        }
    }
    return handler4(str);
}
