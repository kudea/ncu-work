#include<iostream>
#include<string.h>
#include<cstdlib>
#include <fstream>
#include <stdlib.h>
using namespace std;

void selection(int a[],int n){
    int i,j,loc,temp,Min;
    for(i=0;i<n-1;i++){
        Min=a[i];
        loc=i;
        for(j=i+1;j<n;j++){
            if(Min>a[j]){
                Min=a[j];
                loc=j;
            }
        }
        temp=a[i];
        a[i]=a[loc];
        a[loc]=temp;
    }
}
void Merge(int a[],int i1,int j1,int i2,int j2){
    int temp[50];    //array used for merging
    int i,j,k;
    i=i1;    //beginning of the first list
    j=i2;    //beginning of the second list
    k=0;
    while(i<=j1 && j<=j2){    //while elements in both lists

        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    while(i<=j1){    //copy remaining elements of the first list
        temp[k++]=a[i++];
    }
    while(j<=j2){    //copy remaining elements of the second list
        temp[k++]=a[j++];
    }
    //Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++){
        a[i]=temp[j];
    }
}
void mergesort(int a[],int i,int j){
    int mid;
    if(i<j){
        mid=(i+j)/2;
        mergesort(a,i,mid);        //left recursion
        mergesort(a,mid+1,j);    //right recursion
        Merge(a,i,mid,mid+1,j);    //merging of two sorted sub-arrays
    }
}
int main(){
    char ch;
    string str1;
    fstream fs,fp,fm;
    fs.open("input.txt",fstream::in);
    fp.open("output1.txt",fstream::out|fstream::trunc);
    fm.open("output2.txt",fstream::out|fstream::trunc);
    int num=0;
    while(getline(fs,str1)){
        num++;     //ºâ´X¦æ
    }
    fs.close();
    fs.open("input.txt",fstream::in);
    int a[5000];
    int n=0;
    string str2;
    for(int i=0; i<num; i++){
        fs.get(ch);
        while(ch!='\n'){
            if(ch!=' '){
                str2+=ch;
            }
            else{
                a[n]=atoi(str2.c_str());
                n++;
                str2.clear();
            }
            fs.get(ch);
            if(fs.eof()){
                break;
            }
        }
        a[n]=atoi(str2.c_str());
        n++;
        str2.clear();
        selection(a,n);
        for(int i=0;i<n;i++){
            fp<<a[i]<<" ";
        }
        fp<<endl;
        mergesort(a,0,n-1);
        for(int i=0;i<n;i++){
            fm<<a[i]<<" ";
        }
        fm<<endl;
        n=0;
    }
    fs.close();
    fp.close();
    fm.close();
}
