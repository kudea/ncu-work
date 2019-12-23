#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <math.h>
#define STACKSIZE 500
using namespace std;

typedef enum{lparen,rparen,Plus,Minus,times,divide,mod,eos,operand}precedence;
precedence Stack[STACKSIZE];
static int isp[]={0,19,12,12,13,13,13,0};
static int icp[]={20,19,12,12,13,13,13,0};
char expr[STACKSIZE];
int i=0;
struct mainstack{
    int top=-1;
    bool isEmpty(){
        if(top==-1)
            return true;
        else
            return false;
    }
    bool isFull(){
        if(top>=STACKSIZE-1)
            return true;
        else
            return false;
    }
    void Push(precedence x){
        if(isFull()){
            exit(1);
        }
        Stack[top+1]=x;
        top++;
    }
    precedence Pop(){
        if(isEmpty()){
            exit(1);
        }
        return Stack[top--];
    }
};
struct mainstack s;

precedence gotToken(char *symbol,int *n){
    *symbol = expr[(*n)++];
    switch(*symbol){
        case '(' :return lparen;
        case ')' :return rparen;
        case '+' :return Plus;
        case '-' :return Minus;
        case '*' :return times;
        case '/' :return divide;
        case '%' :return mod;
        case '\0':return eos;
        default  :return operand;
    }
}
precedence printToken(precedence t){
    switch(t){
        case lparen:
            expr[i]='(';
            i++;
            break;
        case rparen:
            expr[i]=')';
            i++;
            break;
        case Plus:
            expr[i]='+';
            i++;
            break;
        case Minus:
            expr[i]='-';
            i++;
            break;
        case times:
            expr[i]='*';
            i++;
            break;
        case divide:
            expr[i]='/';
            i++;
            break;
        case mod:
            expr[i]='%';
            i++;
            break;
        case eos:
            expr[i]=' ';
            i++;
            break;
        default :
            expr[i]=' ';
            i++;
    }
}
void postfix(){
    char symbol;
    precedence token;
    int n=0;
    s.top=0;//place eos on stack
    Stack[0]=eos;
    for(token=gotToken(&symbol,&n);token!=eos;token=gotToken(&symbol,&n)){
        if(token==operand){
            expr[i]=symbol;
            i++;
        }
        else if(token==rparen){
            while(Stack[s.top]!=lparen){
                printToken(s.Pop());
            }
            s.Pop();
        }
        else{
            while(isp[Stack[s.top]]>=icp[token]){
                printToken(s.Pop());
            }
            s.Push(token);
        }
    }
    while((token=s.Pop())!=eos){
        printToken(token);
    }
    expr[i]='\0';
}
int e_top=-1;
double e_stack[STACKSIZE];
bool e_isEmpty(){
    if(e_top==-1)
        return true;
    else
        return false;
}
bool e_isFull(){
    if(e_top>=STACKSIZE-1)
        return true;
    else
        return false;
}
void e_Push(double e){
    if(e_isFull()){
        exit(1);
    }
    e_top++;
    e_stack[e_top]=e;
}
double e_Pop(){
    if(e_isEmpty()){
        exit(1);
    }
    return e_stack[e_top--];
}

double eval(){
    precedence token;
    char symbol;
    double op1,op2;
    int n=0;
    token=gotToken(&symbol,&n);
    while(token!=eos){
        if(token==operand)
            e_Push(symbol-'0');//insert stack
        else{
            op2=e_Pop();
            op1=e_Pop();
            switch(token){
                case Plus:
                    e_Push(op1+op2);
                    break;
                case Minus:
                   e_Push(op1-op2);
                    break;
                case times:
                   e_Push(op1*op2);
                    break;
                case divide:
                    e_Push(op1/op2);
                    break;
            }
        }
        token=gotToken(&symbol,&n);
    }
    return e_Pop();//return result
}
int main(){
    fstream fp,fs;
    string str;
    fp.open("input2.txt", fstream::in );
    fs.open("output2.txt",ios::out|ios::trunc);
    fs.close();
    fs.open("output2.txt",ios::out|ios::app);//open a new txt
    while(getline(fp,str)){
        strcpy(expr, str.c_str());
        postfix();
        fs<<expr<<"\n"<<eval()<<"\n";
        i=0;
    }

    fs.close();
    fp.close();
}
