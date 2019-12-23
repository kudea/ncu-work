#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <math.h>
#define MAX 500
#define n 14
using namespace std;
void parsing(char *A);
int isOperand(char ch);    // 判斷是否為運算元 //
int isEmpty(void);        //判斷堆疊是否為空 //
int isFull(void);         // 判斷堆疊是否滿了 //
char pop(void);          //由堆疊取出資料 //
void push(char ch);       //將資料放入堆疊 //
int priority(char op);     //判斷運算符號優先順序//
void inToPostfix(char*, char*); //中序式轉後序式
void intopostfix(char*, char*); // 中序轉後序
int prioritysign(char); // 運算子優先
double eval(char*);
double calcualte(char, double, double);
char Stack[n];
int t=-1;

int main(void) {
    fstream fp,fs;
    fp.open("input2.txt", fstream::in );
    fs.open("output2.txt",fstream::out);//open a new txt
    string str;
    while(getline(fp,str)){
        char postfix1[MAX]={'\0'};
        char infix1[MAX]={'\0'};
        strcpy(infix1, str.c_str());
        inToPostfix(infix1, postfix1);
        int i=0;
        for(i; postfix1[i] != '\0'; i++) {
            fs<<postfix1[i];
        }
        fs<<"\n";
        fs<<round(eval(infix1));
        fs<<"\n";
    }
    fp.close();
    fs.close();
    return 0;
}
void parsing(char *A)
{
	int i,j=0;
	char ch,ch1;
	char B[n];
	for(i=0;i<n-1;i++)
	{
		ch = A[i];
		if(isOperand(ch))
			B[j++]=ch;
		else
		{
			if(ch=='(')
				push(ch);
			else if(ch==')')
			{
				while(!isEmpty())
				{
					ch = pop();
					if(ch=='(')
						break;
					else
						B[j++] = ch;
				}

			}else{

				if(!isEmpty())
				{
					do
					{
						ch1 = pop();

						if(priority(ch1)>priority(ch))
						{
							B[j++] = ch1;
							if(isEmpty())
							{
								push(ch);
								break;
							}
						}
						else{
							push(ch1);
							push(ch);
							break;
						}
					}while(!isEmpty());

				}else{
					push(ch);
				}
			}
		}

	}

	while(!isEmpty())
		B[j++] = pop();


	for(i=0;i<n;i++)
		A[i]=B[i];

}

int isOperand(char ch)
{
	int ret;
	switch(ch)
	{
		case '+':
		case '-':
		case '*':
		case '/':
	    case '(':
		case ')':
			ret = 0;
		break;

default:
			ret = 1;
		break;
	}
	return ret;
}

int isEmpty(void)
{
	if(t==-1)
		return 1;
	else
		return 0;
}

int isFull(void)
{
	if(t==n-1)
		return 1;
	else
		return 0;
}

char pop(void)
{
	char ch = Stack[t];
	Stack[t] = 0;
	t--;
	return ch;
}

void push(char ch)
{
	Stack[++t]=ch;
}

int priority(char op)
{
    int p;

    switch(op) {
       case '+': case '-':
            p = 1;
            break;
        case '*': case '/':
            p = 2;
            break;
        default:
            p = 0;
            break;
    }
    return p;
}
void inToPostfix(char* infix1, char* postfix1) {
    char stack[MAX] = {'\0'};
    int i, j, top;
    for(i = 0, j = 0, top = 0; infix1[i] != '\0'; i++) switch(infix1[i]) {
        case '(':              // 運算子堆疊
            stack[++top] = infix1[i];
            break;
        case '+': case '-': case '*': case '/':
            while(prioritysign(stack[top]) >= priority(infix1[i])) {
                postfix1[j++] = stack[top--];
            }
            stack[++top] = infix1[i]; // 存入堆疊
            break;
        case ')':
            while(stack[top] != '(') { // 遇 ) 輸出至 (
                postfix1[j++] = stack[top--];
            }
            top--;  // 不輸出 (
            break;
        default:  // 運算元直接輸出
            postfix1[j++] = infix1[i];
    }
    while(top > 0) {
        postfix1[j++] = stack[top--];
    }
}
void intopostfix(char* infix1, char* postfix1) {
    char stack[MAX] = {'\0'};
    int i, j, top;
    for(i = 0, j = 0, top = 0; infix1[i] != '\0'; i++) switch(infix1[i]) {
        case '(':              // 運算子堆疊
            stack[++top] = infix1[i];
            break;
        case '+': case '-': case '*': case '/':
            while(prioritysign(stack[top]) >= prioritysign(infix1[i])) {
                postfix1[j++] = stack[top--];
            }
            stack[++top] = infix1[i]; // 存入堆疊
            break;
        case ')':
            while(stack[top] != '(') { // 遇 ) 輸出至 (
                postfix1[j++] = stack[top--];
            }
            top--;  // 不輸出 (
            break;
        default:  // 運算元直接輸出
            postfix1[j++] = infix1[i];
    }
    while(top > 0) {
        postfix1[j++] = stack[top--];
    }
}
int prioritysign(char op) {
    switch(op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    }
}

double eval(char* infix) {
    char postfix[MAX]= {'\0'};
    char opnd[2] = {'\0'};
    double stack[MAX] = {0.0};
    intopostfix(infix, postfix);
    int top, i;
    for(top = 0, i = 0; postfix[i] != '\0'; i++) switch(postfix[i]) {
        case '+': case '-': case '*': case '/':
            stack[top - 1] = calcualte(postfix[i], stack[top - 1], stack[top]);
            top--;
            break;
        default:
            opnd[0] = postfix[i];
            stack[++top] = atof(opnd);//將字串轉為倍精度浮點數
    }
    return stack[top];
}
double calcualte(char op, double p1, double p2) {
    switch(op) {
        case '+': return p1 + p2;
        case '-': return p1 - p2;
        case '*': return p1 * p2;
        case '/': return p1 / p2;
    }
}
