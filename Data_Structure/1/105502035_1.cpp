#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <cstdlib>
using namespace std;
struct Stack {
    int top = -1;
    int STACKSIZE = 500;
    char items [500];

    bool IsEmpty(){
        if(top == -1)
            return true;
        else
            return false;
    }

    bool IsFull (){
        if(top == STACKSIZE-1)
            return true;
        else
            return false;
    }

    int push(char x){
        if(IsFull())
            exit(1);
        else
            items[top+1] = x;
            return top++;
    }

    int pop(){
        if(IsEmpty())
            exit(1);
        else
            return top--;
    }
};
struct Stack mystack;

bool isValid(string s);
bool ifthereisLeft(char c);
bool ifthereisRight(char c);
char getsign(char c);
int main(){
        fstream fp,fs;
        fp.open("input1.txt", fstream::in );
        fs.open("output1.txt",fstream::out);//open a new txt
        string str;
        while(getline(fp,str)){
            if(isValid(str)){
                fs<<"1";
                fs<<"\n";
            }
            else
                fs<<"0";
                fs<<"\n";
                s.top=-1;
        }
    fp.close();
    fs.close();
    return 0;

}
bool isValid(string s) {
    for(int i=0; i<s.length(); i++ ) {
        if (ifthereisLeft( s.at(i) ) ) {
            mystack.push(s.at(i) );
        }
        else if (ifthereisRight(s.at(i)) ) {
            if (mystack.IsEmpty()  ){
                return false;
            }
            char pair = mystack.items[mystack.top];
            mystack.pop();
            char sign = getsign(s.at(i));
            if ( pair != sign ){
                return false;
            }
        }
    }
    if (mystack.IsEmpty() == false ){
        return false;
    }
    else
        return true;

}
bool ifthereisLeft(char c) {
    if ( c == '[' || c == '{' || c == '('){
        return true;
    }
    else
        return false;
}
bool ifthereisRight(char c) {
    if ( c==']' || c=='}' || c==')' )
        return true;
    else
        return false;
}
char getsign(char c) {
    if ( c == ']' )
        return '[';
    else if ( c == '}' )
        return '{';
    else if ( c == ')' )
        return '(';
    else
        return ' ';
}

