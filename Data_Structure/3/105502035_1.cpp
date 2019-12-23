#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>

using namespace std;
int answer[100];
int t=0;
int series=0;//the series of input
struct node{
    int data;
    struct node *leftChild;
    struct node *rightChild;
}*root;

void Insert(node *treePointer, node *newnode){
    if (root == NULL){       //Add Root Node
        root = new node;
        root->data = newnode->data;
        root->leftChild = NULL;
        root->rightChild = NULL;
        return;
    }

    if (treePointer->data > newnode->data){     //Node Added To Left
        if (treePointer->leftChild != NULL){
            Insert(treePointer->leftChild, newnode);
        }
        else{
            treePointer->leftChild = newnode;
            (treePointer->leftChild)->leftChild = NULL;
            (treePointer->leftChild)->rightChild = NULL;
            return;
        }
    }
    else{                //如果數字一樣放在右子樹
        if (treePointer->rightChild != NULL){
            Insert(treePointer->rightChild, newnode);
        }
        else{
            treePointer->rightChild = newnode;
            (treePointer->rightChild)->leftChild = NULL;
            (treePointer->rightChild)->rightChild = NULL;
            return;
        }
    }
}

void Inorder(node *ptr){
    if (ptr != NULL){
        Inorder(ptr->leftChild);
        answer[t]=ptr->data;
        t++;
        Inorder(ptr->rightChild);
    }
}

void Postorder(node *ptr){
    if (ptr != NULL){
        Postorder(ptr->leftChild);
        Postorder(ptr->rightChild);
        answer[t]=ptr->data;
        t++;
    }
}

int main()
{
    root = NULL;
    node *temp;
    char ch;
    fstream fs,fp;
    fs.open("Input1.txt",fstream::in);
    fp.open("Output1.txt",fstream::out|fstream::trunc);
    fs>>series;
    fs.get(ch);
    int num[100];
    int k=0;
    string str;
    for(int i=0; i<series; i++){
            fs.get(ch);
            if(ch==' '|| ch=='\n'){
                fp<<"Tree is empty"<<endl;
            }
            else{
            while(ch!='\n'){
                if(ch!=' '){
                    str+=ch;
                }
                else{
                    num[k]=atoi(str.c_str());
                    k++;
                    str.clear();
                }
                fs.get(ch);
                if(fs.eof()){
                    break;
                }
            }
            num[k]=atoi(str.c_str());
            k++;
            str.clear();
            for(int i=0;i<k;i++){
                temp = new node;
                temp->data=num[i];
                Insert(root, temp);
            }
            k=0;
            fp <<"Inorder: ";
            Inorder(root);
            for(int i=0;i<t;i++){
                fp<<answer[i]<<" ";
            }
            fp<<endl;
            t=0;

            fp <<"Postorder: ";
            Postorder(root);
            for(int i=0;i<t;i++){
                fp<<answer[i]<<" ";
            }
            fp<<endl;
            t=0;
            root=NULL;
        }
            }
        fs.close();
        fp.close();
}
