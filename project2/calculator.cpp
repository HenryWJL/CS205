#include <iostream>
#include "function.cpp"
#include <string>
#include <sstream>
using namespace std;

int fmax(int a,int b){
    return a>b?a:b;
}

bool isNotSmaller(string str1,string str2,int decimal1,int decimal2){      //判断两个正数数字字符串中的前是否大于等于后
    int len1=str1.size();
    int len2=str2.size();
    int num1=len1-decimal1;
    int num2=len2-decimal2;
    if(num1==num2){
        for(int i=0;i<num1;i++){
            if(str1[i]-'0'>str2[i]-'0'){
                return true;
                break;
            }
            else if(str1[i]-'0'<str2[i]-'0'){
                return false;
                break;
            }
        }
        string s1=str1.substr(num1);
        string s2=str2.substr(num2);
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
        return num1>num2?true:false;
    }
}

string handler3(string* str){
    string str1=str[0];
    int decimal=atoi(str[1].c_str());
    string str2,result;
    int power=0;
    stringstream ss;
    bool isNegative=false;
    if(str1[0]=='_'){
        str1=str1.substr(1);
        isNegative=true;
    }
    if(decimal==0){
        if(str1.size()<=10){
            result=str1;
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
                result=str1+".0"+"e"+ss.str(); 
            }
            else{
                str2=str1.insert(1,".");
                result= str2+"e"+ss.str();
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
                    result= str2;
                }
                else{
                    str2=str2.substr(0,i+1);
                    result= str2;
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
                result= str2;
            }
        }
        else{
            power=str1.size()-decimal-1;
            ss<<power;
            if(str1.size()==1){
                result= str1+".0"+"e"+ss.str();
            }
            else{
                str2=str1.insert(1,".");
                int i=str2.size()-1;
                while(str2[i]=='0'){
                    i--;
                }
                str2=str2.substr(0,i+1);
                if(str2.size()==2){
                    result= str2+"0e"+ss.str();
                }
                else{
                    result= str2+"e"+ss.str();
                }
            }
        }
    }
    return isNegative?"_"+result:result;
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
    string * result1=new string[2];
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
    int decimal=fmax(decimal1,decimal2);
    if(isNotSmaller(num1,num2,decimal,decimal)){
        int len1=num1.size();
        int len2=num2.size();
        for(int i=0;i<len1-len2;i++){
            num2='0'+num2;
        }
        int outcome[len1]={};
        for(int i=len1-1;i>=0;i--){
            int n1=num1[i]-'0';
            int n2=num2[i]-'0';
            if(n1<n2){
                outcome[i]=n1+10-n2;
                i--;
                while((num1[i]-'0')<=(num2[i]-'0')){
                    n1=num1[i]-'0';
                    n2=num2[i]-'0';
                    outcome[i]=n1+9-n2;
                    i--;
                }
                n1=num1[i]-'0';
                n2=num2[i]-'0';
                outcome[i]=n1-n2-1;
            }
            else{
                outcome[i]=n1-n2;
            }
        }
        int i=0;
        while(outcome[i]==0&&i<len1){   
            i++;
        }
        if(i==len1){
            result1[0]="0";
            result1[1]="0";
            return result1;
        }
        else{
            for(;i<len1;i++){
                result+=(outcome[i]+'0');
            }
            result1[0]=result;
            ss<<decimal;
            result1[1]=ss.str();
            return result1;
        }
    }
    else{
        //整数位对齐
        int len1=num1.size();
        int len2=num2.size();
        for(int i=0;i<len2-len1;i++){
            num1='0'+num1;
        }
        int outcome[len2]={};
        for(int i=len2-1;i>=0;i--){
            int n1=num1[i]-'0';
            int n2=num2[i]-'0';
            if(n2<n1){
                outcome[i]=n2+10-n1;
                i--;
                while((num2[i]-'0')<=(num1[i]-'0')){
                    n1=num1[i]-'0';
                    n2=num2[i]-'0';
                    outcome[i]=n2+9-n1;
                    i--;
                }
                n1=num1[i]-'0';
                n2=num2[i]-'0';
                outcome[i]=n2-n1-1;
            }
            else{
                outcome[i]=n2-n1;
            }
        }
        int i=0;
        while(outcome[i]==0){
            i++;
        }
        for(;i<len2;i++){
            result+=(outcome[i]+'0');
        }
        result1[0]="_"+result;
        ss<<decimal;
        result1[1]=ss.str();
        return result1;
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
        for(int j=0;j<3;j++){    //保留几位小数(目前是四位)
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
    string * str=new string[2];
    str[0]=max(str1,str2,decimal1,decimal2)[0].compare(str1)==0?str2:str1;
    str[1]=max(str1,str2,decimal1,decimal2)[0].compare(str1)==0?decimal2:decimal1;
    return str;
}

string pow(string str1,string power,int decimal1,int decimal2){
    string result;
    string * str0=new string[2];
    stringstream ss;
    bool isNegative=false;  //输入的str1是否为负数
    int bound,finalDeci;    //bound为power的绝对值，finalDeci为结果的小数位
    string str;             //一个在计算中使用的字符串
    int decimal=decimal1;   //一个在计算中使用的小数位
    //判断输入是否为负
    if(str1[0]=='_'){
        str1=str1.substr(1);
        isNegative=true;
    }
    str=str1;
    //判断power的正负
    if(power[0]=='0'){
        str="0";
        finalDeci=0;
    }
    else if(power[0]=='_'){
        bound=atoi(power.substr(1).c_str());
        for(int i=0;i<bound-1;i++){
            str=multiply(str,str1,decimal,decimal1)[0];
            decimal=atoi(multiply(str,str1,decimal,decimal1)[1].c_str());
        }
        finalDeci=atoi(divide("1",str,0,decimal)[1].c_str());
        str=divide("1",str,0,decimal)[0];
    }
    else{
        bound=atoi(power.c_str());
        for(int i=0;i<bound-1;i++){
            str=multiply(str,str1,decimal,decimal1)[0];
            decimal=atoi(multiply(str,str1,decimal,decimal1)[1].c_str());
        }
        finalDeci=decimal;
    }
    if(isNegative&&bound%2!=0){
        ss<<finalDeci;
        str0[0]=str;
        str0[1]=ss.str();
        result="_"+handler3(str0);
    }
    else{
        ss<<finalDeci;
        str0[0]=str;
        str0[1]=ss.str();
        result=handler3(str0);
    }
    return result;        
}

string* abs(string * str){
    if(str[0][0]=='_'){
        str[0]=str[0].substr(1);
        return str;
    }
    else{
        return str;
    }
}

string * sqrt(string * str){
    if(str[0].compare("0")==0){
        return str;
    }
    else if(str[0].compare("1")==0&&str[1].compare("0")==0){
        return str;
    }
    else{
        string n=handler3(str);
        string w=n+"/2-1";
        string k=CPU(w);
        string str0;
        string str1=k+"*"+k+"-"+n;
        string str2=abs(subCPU(CPU(str1)))[0];
        int str3=atoi(abs(subCPU(CPU(str1)))[1].c_str());
        while(isNotSmaller(str2,"1",str3,1)){
            str0="("+k+"+"+n+"/"+k+")/2";
            k=CPU(str0);
            str1=k+"*"+k+"-"+n;
            str2=abs(subCPU(CPU(str1)))[0];
            str3=atoi(abs(subCPU(CPU(str1)))[1].c_str());
        }
        return subCPU(k);
    }
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
    else if(type=='w'){        //pow{}
        return pow(num1o,num2o,decimal1,decimal2);
    }
    else if(type=='t'){        //sqrt{}
        return handler3(sqrt(str1));
    }
    else{                      //abs{}
        return handler3(abs(str1));
    }    
}
