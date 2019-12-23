#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <math.h>
using namespace std;
typedef enum{lparen,rparen,Plus,Minus,times,divide,mod,eos,operand}precedence;
static int isp[]={0,19,12,12,13,13,13,0};
static int icp[]={20,19,12,12,13,13,13,0};
char expr[500];
int i=0;
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
struct listNode{
    char data;
    listNode *link;
}*top=NULL,*p;

listNode* node(char x){
    p=new listNode;
    p->data=x;
    p->link=NULL;
    return(p);
}

bool isEmpty(){     //linked list is link=top and count down to 0 ,so there is no full situation
    if(top==NULL)
        return true;
    else
        return false;
}

void push(listNode *q){
    if(top==NULL)
        top=q;
    else{
        q->link=top;
        top=q;
    }
}

void pop(){
    if(isEmpty()){
       exit(1);
    }
    else{
        p=top;
        top=top->link;
        delete(p);
    }
}

char getParenthesesPair(char c){   //check if paren are pair
    if ( c == ')' )
        return '(';
    else
        return ' ';
}

int priority(char p){
    switch(p){
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    }
}

double cal(char c, double op1, double op2) {
    switch(c){
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
    }
}

bool isValidout(string str){//check lparen&rparen
    listNode *nptr;
    for(int i=0; i<str.length(); i++ ){
        if(str.at(i) == '(')
        {
            nptr=node(str.at(i));
            push(nptr);
        }
        else if(str.at(i) == ')')
        {
            if(isEmpty())
                return false;
            char compair = top->data;
            pop();
            char ch = getParenthesesPair(str.at(i));
            if(compair != ch)
                return false;
        }
    }
    if (isEmpty () == false)  //check lparen
        return false;
    else
        return true;
}

bool isValidin(string str){//in paren
    int num=0,op=0;
    for(int i=0; i<str.length(); i++ ){
        if(str.at(i)=='0'||str.at(i)=='1'||str.at(i)=='2'||str.at(i)=='3'||str.at(i)=='4'||str.at(i)=='5'||str.at(i)=='6'||str.at(i)=='7'||str.at(i)=='8'||str.at(i)=='9'){
            num++;
        }
        else if(str.at(i)=='+'||str.at(i)=='-'||str.at(i)=='*'|| str.at(i)=='/'){
            op++;
        }
    }
    if((num-op)==1)
        return true;
    else
        return false;
}

void InfixToPostfix(char* infix,char* postfix){
    listNode *nptr;
    int i,j;
    for(i=0,j=0;infix[i]!='\0';i++)switch(infix[i]){
        case '(':              //  put it into stack
            nptr=node(infix[i]);
            push(nptr);
            break;
        case '+': case '-': case '*': case '/':
            while(top!=NULL&&priority(top->data)>=priority(infix[i])){
                postfix[j++]=top->data;
                pop();
            }
            nptr=node(infix[i]);     //存入堆疊
            push(nptr);
            break;
        case ')':
            while(top!=NULL&&(top->data)!='('){     // 遇)輸出至(
                postfix[j++]=top->data;
                pop();
            }
            pop();         // 不輸出 (
            break;
        default:
            postfix[j++]=infix[i];
    }
    while(isEmpty()!=true){            //while stack is not empty, output all elements in stack
        postfix[j++]=top->data;
        pop();
    }
}

double eval(char* infix) {
    char postfix[500]={'\0'};
    char opnd[2]={'\0'};
    double ans[500]={0};
    InfixToPostfix(infix, postfix);
    int i,top;
    for(i=0,top=0;postfix[i]!='\0';i++)switch(postfix[i]){
        case '+': case '-': case '*': case '/':
            ans[top-1]=cal(postfix[i],ans[top-1],ans[top]);
            top--;
            break;
        default:
            opnd[0] = postfix[i];
            ans[++top] = atof(opnd);         //將字串轉為倍精度浮點數(double型態)
    }
    return ans[top];
}

int main(){
        string str;
        fstream fs,fp;
        fs.open("input.txt",fstream::in);
        fp.open("output.txt",fstream::out|fstream::trunc);
        while(getline(fs,str)){
            if(isValidout(str)){
                if(isValidin(str)){
                    char infix[500]={'\0'};
                    char postfix[500]={'\0'};
                    strcpy(infix,str.c_str());//char與str轉換
                    InfixToPostfix(infix,postfix);
                    fp<<postfix;
                    fp<<"\n";
                    fp<<round(eval(infix));
                    fp<<"\n";
                }
                 else{
                    fp<<"The expression is invalid.";
                    fp<<"\n";
                }
            }
            else{
                fp<<"The expression is invalid.";
                fp<<"\n";
            }
           top=NULL;
        }
        fs.close();
        fp.close();
}

