#include <iostream>
#include "function.cpp"
#include <string>
using namespace std;



string handler4(string str){
    bool isInvalid=false;
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
                if(subCPU(num1)[0].compare("Invalid")==0||subCPU(num2)[0].compare("Invalid")==0){
                    isInvalid=true;
                    str="Invalid input";
                }
                else{
                    if(j==0){
                        str=str.replace(0,k-j,calculator(subCPU(num1),subCPU(num2),str[i]));
                    }
                    else{
                        str=str.replace(j+1,k-j-1,calculator(subCPU(num1),subCPU(num2),str[i]));
                    }
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
                if(subCPU(num1)[0].compare("Invalid")==0||subCPU(num2)[0].compare("Invalid")==0){
                    isInvalid=true;
                    str="Invalid input";
                }
                else{
                    if(j==0){
                        str=str.replace(0,k-j,calculator(subCPU(num1),subCPU(num2),str[i]));
                    }
                    else{
                        str=str.replace(j+1,k-j-1,calculator(subCPU(num1),subCPU(num2),str[i]));
                    }
                }
                break;
            }
        }
    }
    return isInvalid?"Invalid input":str;
}

string CPU(string str){
    bool isInvalid=false;
    while(str.find('[')!=string::npos||str.find('(')!=string::npos||str.find('{')!=string::npos){ //不停循环直到去掉所有的括号和数学方法
        if (str.find('[')!=string::npos){  //有[]
            string str1=str.substr(str.find('[')+1,str.find(']')-str.find('[')-1);
            str=str.replace(str.find('['),str.find(']')-str.find('[')+1,CPU(str1));  
        }
        else{  //没有[],但有()或{}
            if(str.find("max{")!=string::npos){
                string str1=str.substr(str.find('{')+1,str.find(',')-str.find('{')-1);
                string str2=str.substr(str.find(',')+1,str.find('}')-str.find(',')-1);
                if(subCPU(str1)[0].compare("Invalid")==0||subCPU(str2)[0].compare("Invalid")==0){
                    isInvalid=true;
                    break;
                }
                else{
                    str=str.replace(str.find("max{"),str.find('}')-str.find("max{")+1,calculator(subCPU(str1),subCPU(str2),'x'));
                }
            }
            else if(str.find("min{")!=string::npos){
                string str1=str.substr(str.find('{')+1,str.find(',')-str.find('{')-1);
                string str2=str.substr(str.find(',')+1,str.find('}')-str.find(',')-1);
                if(subCPU(str1)[0].compare("Invalid")==0||subCPU(str2)[0].compare("Invalid")==0){
                    isInvalid=true;
                    break;
                }
                else{
                    str=str.replace(str.find("min{"),str.find('}')-str.find("min{")+1,calculator(subCPU(str1),subCPU(str2),'n'));
                }
            }
            else if(str.find("pow{")!=string::npos){
                string str1=str.substr(str.find('{')+1,str.find(',')-str.find('{')-1);
                string str2=str.substr(str.find(',')+1,str.find('}')-str.find(',')-1);
                if(subCPU(str1)[0].compare("Invalid")==0||subCPU(str2)[0].compare("Invalid")==0){
                    isInvalid=true;
                    break;
                }
                else{
                    str=str.replace(str.find("pow{"),str.find('}')-str.find("pow{")+1,calculator(subCPU(str1),subCPU(str2),'w'));
                }
            }
            else if(str.find("abs{")!=string::npos){
                string str1=str.substr(str.find('{')+1,str.find('}')-str.find('{')-1);
                string str2="0";
                if(subCPU(str1)[0].compare("Invalid")==0){
                    isInvalid=true;
                    break;
                }
                else{
                    str=str.replace(str.find("abs{"),str.find('}')-str.find("abs{")+1,calculator(subCPU(str1),subCPU(str2),'s'));
                }
            }
            else if(str.find("sqrt{")!=string::npos){
                string str1=str.substr(str.find('{')+1,str.find('}')-str.find('{')-1);
                string str2="0";
                if(subCPU(str1)[0].compare("Invalid")==0){
                    isInvalid=true;
                    break;
                }
                else{
                    str=str.replace(str.find("sqrt{"),str.find('}')-str.find("sqrt{")+1,calculator(subCPU(str1),subCPU(str2),'t'));
                    
                }
            }
            else{   //加减乘除
                string str1=str.substr(str.find('(')+1,str.find(')')-str.find('(')-1);
                if(handler4(str1).compare("Invalid input")==0){
                    isInvalid=true;
                    break;
                }
                else{
                    str=str.replace(str.find('('),str.find(')')-str.find('(')+1,handler4(str1));
                }
            }
        }
    }
    return isInvalid?"Invalid input":handler4(str);
}
