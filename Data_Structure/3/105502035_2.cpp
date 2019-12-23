#include<iostream>
#include<string>
#include<queue>
#include<cstdlib>
#include <fstream>
using namespace std;
int k=0,j=0;/**k算Input中的數字   j算Input中的字母*****/
string storenumber[100];
string storealph[100];
int number=0;/**計算array中的位置**/
class node{
     public:
        node(string con, float wht, node* left, node* right, string co ){
            content=con;
            weight=wht;
            leftchild=left;
            rightchild=right;
            code=co;
        }
        string content;
        float weight;
        node* leftchild;
        node* rightchild;
        string code;
};
void insertion_sort(node** array, int low, int high){
    for(int i=low+1;i<high;i++){
        node* tem=array[i];
        int j=i-1;
        while(array[j]->weight>tem->weight&&j>=low){
            array[j+1]=array[j];
            j--;
        }
        array[j+1]=tem;
    }
}
void create_huffman_tree(string* s, int* w,int n,node** array){
    for(int i=0;i<n;i++){
        array[i]=new node(s[i],w[i],NULL,NULL,"");
    }
    insertion_sort(array,0,n);

    int p=0;
    while(p!=n-1){
        node* min_1=array[p];
        node* min_2=array[p+1];
        node* new_node=new node("",min_1->weight+min_2->weight,min_1,min_2,"");
        array[p+1]=new_node;
        p=p+1;
        insertion_sort(array,p,n);
    }
}
void create_huffman_code(node* p){
    queue<node*> nq;
    nq.push(p);
    while(nq.size()!=0){
        node* cur=nq.front();
        nq.pop();
        node* l=cur->leftchild;
        if(l!=NULL){l->code=cur->code+"0"; nq.push(l);}
        node* r=cur->rightchild;
        if(r!=NULL){r->code=cur->code+"1"; nq.push(r);}
        if(l==NULL&&r==NULL){
            storealph[number]=cur->content;
            storenumber[number]=cur->code;
            number++;
        }
    }
}
int main(){
        string str1;
        fstream fs,fp;
        fs.open("Input2.txt",fstream::in);                          //open the file
        fp.open("Output2.txt",fstream::out|fstream::trunc);        //write the file
        int line = 0;
        while(getline(fs,str1)){
            line++;     //算幾行
        }
        /************************************分開的目的是為了防止2邊的檔案互相混雜***********************************/
        /**********先算Input有幾行   再計算Input中的某行  他其中的字串*****/
        fs.close();
        fs.open("Input2.txt",fstream::in);
        /************/
        int num[100];/******對照上面函式void create_huffman_tree(string* s, int* w,int n,node** array)****/
        string alph[100];
        /*************/
        char ch;
        string str2;
        int valid=1;
        for(int i=0; i<line; i++){
            fs.get(ch);
            while(ch!='\n'){
                if(ch!=':'&&ch!=','){
                    if(ch==' '){
                       valid=0;
                    }
                    else{
                       str2+=ch;
                    }
                }
                else if(ch==':'){
                    alph[j]=str2;
                    j++;
                    str2.clear();
                }
                else if(ch==','){
                    num[k]=atoi(str2.c_str());
                    k++;
                    str2.clear();
                }
                fs.get(ch);
                if(fs.eof()){
                    break;
                }
            }
            if(ch==' '){
                valid=0;
            }
            else{
                num[k]=atoi(str2.c_str());
                k++;
                str2.clear();
            }
            node* array[k];
            create_huffman_tree(alph,num,k,array);
            create_huffman_code(array[k-1]);
            if(valid==0){
                fp<<"error";
            }
            else if(j==1&&k==1){//避免讀取空白
                fp<<"error";
            }
            else{
                for(int a=0;a<k;a++){        //compare讀檔順序跟queue
                    for(int b=0;b<k;b++){
                        if(alph[a]==storealph[b]){
                            fp<<storealph[b]<<":"<<storenumber[b];
                        }
                    }
                    if(a!=k-1){//輸出完數字後 輸出，做分隔
                        fp<<",";
                    }
                }
                fp<<endl;
            }
            k=0;
            j=0;
            number=0;
            valid=1;
        }
        fs.close();
        fp.close();
}
