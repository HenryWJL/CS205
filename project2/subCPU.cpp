#include <iostream>
#include "function.h"
#include <string>
#include <sstream>
using namespace std;

int judge(string str){
    int a=0;                  //输出：a=0正常整数或浮点数，a=1科学计数法，a=2 invalid字符
    int cnt1=0;               //计算e的个数
    int cnt2=0;               //计算.的个数
    int cnt3=0;               //计算-的个数
    int ePlace=10000;         //存储e的位置
    int dotPlace=-1;          //存储.的位置
    for(int i=0;i<str.size();i++){
        if(str[i]-'0'>=0&&str[i]-'0'<=9){
            continue;
        }
        else if(str[i]=='e'){
            cnt1++;
            ePlace=i;
            if(cnt1>=2||dotPlace>ePlace){      //e多于一个或e在.之前都invalid
                a=2;
                break;
            }
            else{
                a=1;
            }
        }
        else if(str[i]=='.'){
            cnt2++;
            dotPlace=i;
            if(cnt2>=2||dotPlace>ePlace){      //.多于一个或e在.之前都invalid
                a=2;
                break;
            }
            else{
                a=0;
            }
        }
        else if(str[i]=='_'){
            cnt3++;
            if(cnt3>=3){
                a=2;
                break;
            }
            else{
                if(i>ePlace){                  //对应科学计数法
                    a=1;
                }
                else{
                    a=0;
                }
            }
        }
        else{
            a=2;
            break;
        }
    }
    if(a==1){                                 //检测.和e之间的小数部分是否缺失以及e,.是否在开头和结尾
        if(ePlace-dotPlace==1||ePlace==0||dotPlace==0||ePlace==str.size()-1||dotPlace==str.size()-1){
            a=2;
        }
    }

    return a;
}

string* handler1(string str){                //处理一般整数和浮点数，转化成整数+小数位的形式
    int decimal=0;                           //小数位
    stringstream ss;
    string* s=new string[2];
    for(int i=0;i<str.size();i++){
        if(str[i]=='.'){
            decimal=str.size()-i-1;
            break;
        }
    }
    ss<<decimal;
    if(decimal==0){
        s[0]=str;
        s[1]="0";
        return s;
    }
    else{
        if(str[0]=='0'){
            int i=2;
            while(str[i]=='0'){
                i++;
            }
            s[0]=str.substr(i,str.size());
            s[1]=ss.str();
            return s;
        }
        else if(str[0]=='_'&&str[1]=='0'){
            int i=3;
            while(str[i]=='0'){
                i++;
            }
            s[0]="_"+str.substr(i,str.size());
            s[1]=ss.str();
            return s;
        }
        else{
            s[0]=str.replace(str.find('.'),1,"");
            s[1]=ss.str();
            return s;
        }
    }
}

string* handler2(string str){                      //处理科学计数法
    
    string result="";
    int dotPlace=str.find('.');
    int ePlace=str.find('e');
    string integer=str.substr(0,dotPlace);                //整数部分
    
    string decimal=str.substr(dotPlace+1,ePlace-dotPlace-1);//小数部分
    
    string power0=str.substr(ePlace+1,str.size()-ePlace);
    int power=0;
    if(power0[0]=='_'){                                 
        power=0-atoi(power0.substr(1).c_str()); 
    }                                                     //幂
    else{
        power=atoi(power0.c_str());
    }   

    if(str.find('.')==string::npos){               //e前为整数
        integer=str.substr(0,ePlace);
        if(power>=0){
            result=integer;
            for(int i=0;i<power;i++){
                result+='0';
            }
            return handler1(result);
        }
        else{
            if(abs(power)>=integer.size()){
                result="0.";
                for(int i=0;i<abs(power)-integer.size();i++){
                    result+='0';
                }
                result+=integer;
                return handler1(result);
            }
            else{
                result=integer;
                result=result.insert(integer.size()-abs(power),".");
                return handler1(result);
            }
        }
        
    }
    else{                                          //e前为浮点数
        if(power>=decimal.size()&&power>=0){
            result=integer+decimal;
            for(int i=0;i<(power-decimal.size());i++){
                result+='0';
            }
            return handler1(result);
        }
        else if(power<decimal.size()&&power>=0){
            result=integer;
            int i=0;
            for(;i<power;i++){
                result+=decimal[i];
            }
            result+='.';
            for(;i<decimal.size();i++){
                result+=decimal[i];
            }
            return handler1(result);
        }
        else{           
            
            if(abs(power)<integer.size()){
                result=integer;
                result=result.insert(integer.size()-abs(power),".");
                result+=decimal;
                return handler1(result);
            }
            else {
                result="0.";
                for(int i=0;i<abs(power)-integer.size();i++){
                    result+='0';
                }
                result=result+integer+decimal;
                return handler1(result);
            }
        }
    }
}

string* subCPU(string str){
    int type=judge(str);
    string* s=new string[2];
    s[0]="Invalid";
    s[1]="Invalid";
    switch (type)
    {
    case 0:
        return handler1(str);
        break;
    case 1:
        return handler2(str);
        break;
    default:
        return s;
        break;
    }
}
