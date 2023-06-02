/*
 * Before using the device, please read the following manual.
 *
 * This calculator receives two inputs of specific types, including:
 *
 * 1.Integer numbers:
 *
 * eg. 0, -1, 13...
 *
 * 2.Floating-point numbers:
 *
 * eg. -0.23, 1.46, 3.1415...
 *
 * 3.Numbers written in scientific notation:
 * 
 * eg. 2.0e20, 1.48e-15, -3e9...
 * 
 * Inputs of any other types will be treated as invalid inputs.
 * 
 * eg. a, b_f_g, -2-4, 2ee03...
 * 
 * Caution: Inputs in the form of 2.e10, .4 are also invalid!
 * 
 */



#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <cmath>
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
        else if(str[i]=='-'){
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

bool isPositive(string str){                  //判断正负
    if(str[0]=='-'){
        return false;
    }
    else{
        return true;
    }
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
        else if(str[0]=='-'&&str[1]=='0'){
            int i=3;
            while(str[i]=='0'){
                i++;
            }
            s[0]="-"+str.substr(i,str.size());
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

    int power=atoi(power0.c_str());                //幂

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
            if(integer.compare("0")==0){
                result=decimal;
            }
            else{
                result=integer+decimal;
            }
            for(int i=0;i<(power-decimal.size());i++){
                result+='0';
            }
            return handler1(result);
        }
        else if(power<decimal.size()&&power>=0){
            result=integer+decimal;
            result=result.insert(dotPlace+power,".");
            int i=0;
            while(result[i]=='0'&&i<result.find('.')-1){
                i++;
            }
            result=result.substr(i);
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

string handler3(string* str){
    string str1=str[0];
    int decimal=atoi(str[1].c_str());
    string str2="";
    int power=0;
    stringstream ss;
    if(decimal==0){
        if(str1.size()<=10){
            return str1;
        }
        else{
            power=str1.size()-1;
            ss<<power;
            int i=str1.size()-1;
            while(str1[i]=='0'){
                i--;
            }
            str1=str1.substr(0,i+1);
            if(str1.size()==1){
                return str1+".0"+"e"+ss.str();
            }
            else{
                str2=str1.insert(1,".");
                return str2+"e"+ss.str();
            }
        }
    }
    else{
        int diff=str1.size()-decimal;
        if(abs(diff)<=10){
            if(decimal<str1.size()){
                str2=str1.insert(str1.size()-decimal,".");
                int i=str2.size()-1;
                while(str2[i]=='0'){
                    i--;
                }
                
                if(str1[i]=='.'){
                    str2=str2.substr(0,i);
                    return str2;
                }
                else{
                    str2=str2.substr(0,i+1);
                    return str2;
                }
            }
            else{
                str2="0.";
                for(int i=0;i<decimal-str1.size();i++){
                    str2+='0';
                }
                str2=str2+str1;
                int i=str2.size()-1;
                while(str2[i]=='0'){
                    i--;
                }
                str2=str2.substr(0,i+1);
                return str2;
            }
        }
        else{
            power=str1.size()-decimal-1;
            ss<<power;
            if(str1.size()==1){
                return str1+".0"+"e"+ss.str();
            }
            else{
                str2=str1.insert(1,".");
                int i=str2.size()-1;
                while(str2[i]=='0'){
                    i--;
                }
                str2=str2.substr(0,i+1);
                if(str2.size()==2){
                    return str2+"0e"+ss.str();
                }
                else{
                    return str2+"e"+ss.str();
                }
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

string* calculator(string* num1_,string* num2_){
    
    //确定小数位
    int decimal1=atoi(num1_[1].c_str());   
    int decimal2=atoi(num2_[1].c_str());
    
    string num1o=num1_[0];
    string num2o=num2_[0];
    string num1="";
    string num2="";
    for(int i=0;i<num1o.size();i++){
        num1+=num1o[num1o.size()-1-i];
    }
    for(int i=0;i<num2o.size();i++){
        num2+=num2o[num2o.size()-1-i];
    }
    
    int result0[num1.size()+num2.size()]={0};
    
    string result="";
    string decimal="";
    string* finalResult=new string[2];

    for(int i=0;i<num1.size();i++){    
        for(int j=0;j<num2.size();j++){
            int n1=num1[i]-'0';
            int n2=num2[j]-'0';
            if(n1*n2>=10){
                int proceed=n1*n2/10;             //进位
                result0[i+j+1]+=proceed;
                result0[i+j]+=n1*n2%10;
            }
            else{
                result0[i+j]+=n1*n2;
            }
        }
    }
    
    
    //再进位一次
    for(int i=0;i<num1.size()+num2.size();i++){   
        if(result0[i]>=10){
            int proceed=result0[i]/10;
            result0[i+1]+=proceed;
            result0[i]%=10;
        }
    }
    
    
    //防止result0最后几位为0导致reverse后结果开头为0
    int i=0;
    while(result0[num1.size()+num2.size()-1-i]==0&&i<=num1.size()+num2.size()-1){
        i++;
    }
    if(i==num1.size()+num2.size()){
        finalResult[0]="0";
        finalResult[1]="0";
    }
    else{
        for(int j=num1.size()+num2.size()-1-i;j>=0;j--){
            result+=(result0[j]+'0');
        }
        stringstream ss;
        ss<<(decimal1+decimal2);
        ss>>decimal;
        finalResult[0]=result;
        finalResult[1]=decimal;
    }   
    return finalResult;
    
}

string CPU(string num1_,string num2_){
    bool b1=isPositive(num1_);
    bool b2=isPositive(num2_);
    string* num1=subCPU(num1_);
    string* num2=subCPU(num2_);
    if(num1[0].compare("Invalid")==0||num2[0].compare("Invalid")==0){
        return "The input cannot be interpreted as numbers!";
    }
    else if(b1&&b2){
        return handler3(calculator(num1,num2));
    }
    else if(!b1&&!b2){
        num1[0]=num1[0].replace(0,1,"");
        num2[0]=num2[0].replace(0,1,"");
        return handler3(calculator(num1,num2));
    }
    else if(b1&&!b2){
        num2[0]=num2[0].replace(0,1,"");
        return "-"+handler3(calculator(num1,num2));
    }
    else{
        num1[0]=num1[0].replace(0,1,"");
        return "-"+handler3(calculator(num1,num2));
    }
}

int main(){
    string num1,num2;
    cin>>num1>>num2;
    cout<<CPU(num1,num2)<<endl;
    return 0;
}
