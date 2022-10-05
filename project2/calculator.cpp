#include <iostream>
#include "function.cpp"
#include <string>
#include <sstream>
using namespace std;

int fmax(int a,int b){
    return a>b?a:b;
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

string* add(string num1,string num2,int decimal1,int decimal2){
    stringstream ss;
    string result="";
    //小数位对齐
    if(decimal1-decimal2<0){
        for(int i=0;i<decimal2-decimal1;i++){
            num1=num1+'0';
        }
    }
    else{
        for(int i=0;i<decimal1-decimal2;i++){
            num2=num2+'0';
        }
    }
    //整数位对齐
    if(num1.size()>num2.size()){
        int len1=num1.size();
        int len2=num2.size();
        for(int i=0;i<len1-len2;i++){
            num2='0'+num2;
        }
    }
    else{
        int len1=num1.size();
        int len2=num2.size();
        for(int i=0;i<len2-len1;i++){
            num1='0'+num1;
        }
    }
       
    int outcome[num1.size()+1]={};
    for(int i=num1.size();i>0;i--){
        int n1=num1[i-1]-'0';
        int n2=num2[i-1]-'0';
        if(n1+n2+outcome[i]>=10){
            outcome[i]+=n1+n2-10;
            outcome[i-1]+=1;
        }
        else{
            outcome[i]+=(n1+n2);
        }
    }
        
    if(outcome[0]==0){
        for(int i=1;i<num1.size()+1;i++){
            result+=(outcome[i]+'0');
        }
    }
    else{
        for(int i=0;i<num1.size()+1;i++){
            result+=(outcome[i]+'0');
        }
    }
    string * result1=new string[2];
    result1[0]=result;
    ss<<fmax(decimal1,decimal2);
    result1[1]=ss.str();
    return result1;
}

string* subtract(string num1,string num2,int decimal1,int decimal2){
    stringstream ss;
    string result="";
    //小数位对齐
    if(decimal1-decimal2<0){
        for(int i=0;i<decimal2-decimal1;i++){
            num1=num1+'0';
        }
    }
    else{
        for(int i=0;i<decimal1-decimal2;i++){
            num2=num2+'0';
        }
    }
    
    if(num1.size()>num2.size()){     //num1>num2
        //整数位对齐
        int len1=num1.size();
        int len2=num2.size();
        for(int i=0;i<len1-len2;i++){
            num2='0'+num2;
        }
        int outcome[num1.size()]={};
        for(int i=num1.size()-1;i>=0;i--){
            int n1=num1[i]-'0';
            int n2=num2[i]-'0';
            if(n1<n2){
                outcome[i]=n1+10-n2;
                i--;
                while((num1[i]-'0')<=(num2[i]-'0')){
                    outcome[i]=n1+9-n2;
                    i--;
                }
                outcome[i]=num1[i]-num2[i]-1;
            }
            else{
                outcome[i]=n1-n2;
            }
        }
        int i=0;
        while(outcome[i]==0){
            i++;
        }
        for(;i<num1.size();i++){
            result+=(outcome[i]+'0');
        }
        string * result1=new string[2];
        result1[0]=result;
        ss<<fmax(decimal1,decimal2);
        result1[1]=ss.str();
        return result1;
    }
    else if(num1.size()<num2.size()){     //num1<num2
        //整数位对齐
        int len1=num1.size();
        int len2=num2.size();
        for(int i=0;i<len2-len1;i++){
            num1='0'+num1;
        }
        int outcome[num1.size()]={};
        for(int i=num1.size()-1;i>=0;i--){
            int n1=num1[i]-'0';
            int n2=num2[i]-'0';
            if(n2<n1){
                outcome[i]=n2+10-n1;
                i--;
                while((num2[i]-'0')<=(num1[i]-'0')){
                    outcome[i]=n2+9-n1;
                    i--;
                }
                outcome[i]=num2[i]-num1[i]-1;
            }
            else{
                outcome[i]=n2-n1;
            }
        }
        int i=0;
        while(outcome[i]==0){
            i++;
        }
        for(;i<num1.size();i++){
            result+=(outcome[i]+'0');
        }
        string * result1=new string[2];
        result1[0]="_"+result;
        ss<<fmax(decimal1,decimal2);
        result1[1]=ss.str();
        return result1;
    }
    else{
        int a=0;
        for(int i=0;i<num1.size();i++){
            if((num1[i]-'0')>(num2[i]-'0')){
                a=1;
                break;
            }
            else if((num1[i]-'0')<(num2[i]-'0')){
                a=2;
                break;
            }
        }
        if(a==0){     //num1=num2
            string * result1=new string[2];
            result1[0]="0";
            result1[1]="0";
            return result1;
        }
        else if(a==1){     //num1>num2
            int outcome[num1.size()]={};
            for(int i=num1.size()-1;i>=0;i--){
                int n1=num1[i]-'0';
                int n2=num2[i]-'0';
                if(n1<n2){
                    outcome[i]=n1+10-n2;
                    i--;
                    while((num1[i]-'0')<=(num2[i]-'0')){
                        outcome[i]=n1+9-n2;
                        i--;
                    }
                    outcome[i]=num1[i]-num2[i]-1;
                }
                else{
                    outcome[i]=n1-n2;
                }
            }
            int i=0;
            while(outcome[i]==0){
                i++;
            }
            for(;i<num1.size();i++){
                result+=(outcome[i]+'0');
            }
            string * result1=new string[2];
            
            result1[0]=result;
            ss<<fmax(decimal1,decimal2);
            result1[1]=ss.str();
            return result1;
        }
        else{    //num1<num2
            int outcome[num1.size()]={};
            for(int i=num1.size()-1;i>=0;i--){
                int n1=num1[i]-'0';
                int n2=num2[i]-'0';
                if(n2<n1){
                    outcome[i]=n2+10-n1;
                    i--;
                    while((num2[i]-'0')<=(num1[i]-'0')){
                        outcome[i]=n2+9-n1;
                        i--;
                    }
                    outcome[i]=num2[i]-num1[i]-1;
                }
                else{
                    outcome[i]=n2-n1;
                }
            }
            int i=0;
            while(outcome[i]==0){
                i++;
            }
            for(;i<num1.size();i++){
                result+=(outcome[i]+'0');
            }
            string * result1=new string[2];
            result1[0]="_"+result;
            ss<<fmax(decimal1,decimal2);
            result1[1]=ss.str();
            return result1;
        }
    }
}

string* multiply(string str1,string str2,int decimal1,int decimal2){
    string num1o=str1;
    string num2o=str2;
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

bool isNotSmaller(string str1,string str2,int decimal1,int decimal2){      //判断两个正数数字字符串中的前是否大于等于后
    if(str1.size()-decimal1==str2.size()-decimal2){
        for(int i=0;i<str1.size()-decimal1;i++){
            if(str1[i]-'0'>str2[i]-'0'){
                return true;
                break;
            }
            else if(str1[i]-'0'<str2[i]-'0'){
                return false;
                break;
            }
        }
        string s1=str1.substr(str1.size()-decimal1);
        string s2=str2.substr(str2.size()-decimal2);
        if(s1.size()==s2.size()){
            for(int i=0;i<s1.size();i++){
                if(s1[i]-'0'>s2[i]-'0'){
                    return true;
                    break;
                }
                else if(s1[i]-'0'<s2[i]-'0'){
                    return false;
                    break;
                }
            }
            return true;
        }
        else{
            return s1.size()>s2.size()?true:false;
        }
    }
    else{
        return str1.size()-decimal1>str2.size()-decimal2?true:false;
    }
    // if(str1.size()>str2.size()){
    //     return true;
    // }
    // else if(str1.size()<str2.size()){
    //     return false;
    // }
    // else{
    //     for(int i=0;i<str1.size();i++){
    //         if((str1[i]-'0')>(str2[i]-'0')){
    //             return true;
    //             break;
    //         }
    //         else if((str1[i]-'0')<(str2[i]-'0')){
    //             return false;
    //             break;
    //         }
    //     }
    //     return true;
    // }
}


string* divide(string str1,string str2,int decimal1,int decimal2){
    int decimal=decimal1-decimal2;
    string num1=str1;
    string num2=str2;
    string result="";
    int integer=0;      //结果的整数部分
    while(isNotSmaller(num1,num2,0,0)){
        num2=add(num2,str2,0,0)[0];
        integer++;
    }
    stringstream ss;
    ss<<integer;
    string remainder=subtract(num1,multiply(str2,ss.str(),0,0)[0],0,0)[0];
    ss.str("");     //清除缓存
    if(remainder.compare("0")!=0){
        int i=0;
        while(!isNotSmaller(remainder,str2,0,0)){   //余数补0
            remainder+="0";
            i++;
        }
        for(int j=0;j<3;j++){       //保留几位小数（目前是四位）
            remainder+="0";
        }    
        decimal+=(i+3);
    }
    else{
        decimal+=1;
    }
    int deci=0;     //结果的小数部分
    num2=str2;
    while(isNotSmaller(remainder,num2,0,0)){
        num2=add(num2,str2,0,0)[0];
        deci++;
    }
    if(integer!=0){
        ss<<integer;
        result+=ss.str();
        ss.str("");
    }
    ss<<deci;
    result+=ss.str();
    ss.str("");
    string * str=new string[2];
    if(decimal<0){
        for(int j=0;j<abs(decimal);j++){
            result+="0";
        }
        str[0]=result;
        str[1]="0";
        return str;
    }
    else{
        str[0]=result;
        ss<<decimal;
        str[1]=ss.str();
        return str;
    }
}

string* max(string str1,string str2,int decimal1,int decimal2){
    string* str=new string[2];
    stringstream ss;
    ss<<decimal1;
    string deci1=ss.str();
    ss.str("");
    ss<<decimal2;
    string deci2=ss.str();
    
    if(str1[0]!='_'&&str2[0]!='_'){
        str[0]=isNotSmaller(str1,str2,decimal1,decimal2)?str1:str2;
        str[1]=isNotSmaller(str1,str2,decimal1,decimal2)?deci1:deci2;
    }
    else if(str1[0]=='_'&&str2[0]=='_'){
        str[0]=isNotSmaller(str1,str2,decimal1,decimal2)?str2:str1;
        str[1]=isNotSmaller(str1,str2,decimal1,decimal2)?deci2:deci1;
    }
    else if(str1[0]!='_'&&str2[0]=='_'){
        str[0]=str1;
        str[1]=deci1;
    }
    else{
        str[0]=str2;
        str[1]=deci2;
    }
    return str;
}

string* min(string str1,string str2,int decimal1,int decimal2){
    return max(str2,str1,decimal2,decimal1);
}

string* pow(string str1,string power,int decimal1,int decimal2){
    string* str0=new string[2];
    stringstream ss;
    if(power[0]=='0'){
        str0[0]="1";
        str0[1]="0";
    }
    else if(power[0]=='_'){
        int bound=atoi(power.substr(1).c_str());
        string str=str1;
        int decimal=decimal1;
        for(int i=0;i<bound-1;i++){
            str=multiply(str,str1,decimal,decimal1)[0];
            decimal=atoi(multiply(str,str1,decimal,decimal1)[1].c_str());
        }
        int deci=atoi(divide("1",str,0,decimal)[1].c_str());
        str=divide("1",str,0,decimal)[0];
        ss<<deci;
        str0[0]=str;
        str0[1]=ss.str();
    }
    else{
        int bound=atoi(power.c_str());
        string str=str1;
        int decimal=decimal1;
        for(int i=0;i<bound-1;i++){
            str=multiply(str,str1,decimal,decimal1)[0];
            decimal=atoi(multiply(str,str1,decimal,decimal1)[1].c_str());
        }
        ss<<decimal;
        str0[0]=str;
        str0[1]=ss.str();
    }
    return str0;        
}


string calculator(string * str1,string * str2,char type){   //type指加减乘除和数学方法中的一种
    string num1o=str1[0];
    string num2o=str2[0];
    int decimal1=atoi(str1[1].c_str());
    int decimal2=atoi(str2[1].c_str());
    string num1;
    string num2;


    //加法
    if(type=='+'){
        if(num1o[0]!='_'&&num2o[0]!='_'){
            return handler3(add(num1o,num2o,decimal1,decimal2));
        }
        else if(num1o[0]=='_'&&num2o[0]=='_'){
            num1=num1o.substr(1,num1o.size());
            num2=num2o.substr(1,num2o.size());
            return "_"+handler3(add(num1,num2,decimal1,decimal2));
        }
        else if(num1o[0]!='_'&&num2o[0]=='_'){
            num1=num1o;
            num2=num2o.substr(1,num2o.size());
            return handler3(subtract(num1,num2,decimal1,decimal2));
        }
        else{
            num1=num1o.substr(1,num1o.size());
            num2=num2o;
            return handler3(subtract(num2,num1,decimal2,decimal1));
        }
    }
    
    //减法
    else if(type=='-'){
        if(num1o[0]!='_'&&num2o[0]!='_'){
            return handler3(subtract(num1o,num2o,decimal1,decimal2));
        }
        else if(num1o[0]=='_'&&num2o[0]=='_'){
            num1=num1o.substr(1,num1o.size());
            num2=num2o.substr(1,num2o.size());
            string str=handler3(subtract(num1,num2,decimal1,decimal2));
            if(str[0]=='_'){
                return str.substr(1,str.size());
            }
            else{
                return "_"+str;
            }
        }
        else if(num1o[0]!='_'&&num2o[0]=='_'){
            num1=num1o;
            num2=num2o.substr(1,num2o.size());
            return handler3(add(num1,num2,decimal1,decimal2));
        }
        else{
            num1=num1o.substr(1,num1o.size());
            num2=num2o;
            return "_"+handler3(add(num2,num1,decimal2,decimal1));
        }
    }

    //乘法
    else if(type=='*'){
        if(num1o[0]!='_'&&num2o[0]!='_'){
            return handler3(multiply(num1o,num2o,decimal1,decimal2));
        }
        else if(num1o[0]=='_'&&num2o[0]=='_'){
            num1=num1o.substr(1,num1o.size());
            num2=num2o.substr(1,num2o.size());
            return handler3(multiply(num1,num2,decimal1,decimal2));
        }
        else if(num1o[0]!='_'&&num2o[0]=='_'){
            num1=num1o;
            num2=num2o.substr(1,num2o.size());
            return "_"+handler3(multiply(num1,num2,decimal1,decimal2));
        }
        else{
            num1=num1o.substr(1,num1o.size());
            num2=num2o;
            return "_"+handler3(multiply(num2,num1,decimal2,decimal1));
        }
    }
    //除法
    else if(type=='/'){
        if(num1o[0]!='_'&&num2o[0]!='_'){
            return handler3(divide(num1o,num2o,decimal1,decimal2));
        }
        else if(num1o[0]=='_'&&num2o[0]=='_'){
            num1=num1o.substr(1,num1o.size());
            num2=num2o.substr(1,num2o.size());
            return handler3(divide(num1,num2,decimal1,decimal2));
        }
        else if(num1o[0]!='_'&&num2o[0]=='_'){
            num1=num1o;
            num2=num2o.substr(1,num2o.size());
            return "_"+handler3(divide(num1,num2,decimal1,decimal2));
        }
        else{
            num1=num1o.substr(1,num1o.size());
            num2=num2o;
            return "_"+handler3(divide(num1,num2,decimal1,decimal2));
        }
    }
    else if(type=='x'){        //max{}
        return handler3(max(num1o,num2o,decimal1,decimal2));
    }
    else if(type=='n'){        //min{}
        return handler3(min(num1o,num2o,decimal1,decimal2));
    }
    else {                     //pow{}
        return handler3(pow(num1o,num2o,decimal1,decimal2));
    }    
}
