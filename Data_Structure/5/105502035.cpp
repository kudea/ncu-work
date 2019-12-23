#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
using namespace std;
/*** a structure to represent a weighted edge in graph***/
struct Edge1{
    int src,dest,weight;
};
/*** a structure to represent a connected, undirected***/
/*** and weighted graph***/
struct Graph1{
    /*** V-> Number of vertices, E-> Number of edges***/
    int V1, E1;
    /*** graph is represented as an array of edges.***/
    /*** Since the graph is undirected, the edge***/
    /*** from src to dest is also edge from dest***/
    /*** to src. Both are counted as 1 edge here.***/
    struct Edge1* edge1;
};
/*** Creating shortcut for an integer pair***/
typedef  pair<int,int>iPair;
/*** Structure to represent a graph***/
struct Graph{
    int V,E;
    vector<pair<int,iPair> >edges;
    /*** Constructor***/
    Graph(int V, int E){
        this->V=V;
        this->E=E;
    }
    /*** Utility function to add an edge***/
    void addEdge(int u,int v,int w){
        edges.push_back({w,{u,v}});
    }
    /*** Function to find MST using Kruskal's***/
    /*** MST algorithm***/
    int kruskalMST();
};
/*** To represent Disjoint Sets**/
struct DisjointSets{
    int *parent,*rnk;
    int n;
    /*** Constructor.***/
    DisjointSets(int n){
       /*** Allocate memory***/
        this->n=n;
        parent=new int[n+1];
        rnk=new int[n+1];
        /*** Initially, all vertices are in***/
        /*** different sets and have rank 0.***/
        for(int i=0;i<=n;i++){
            rnk[i]=0;
            /***every element is parent of itself***/
            parent[i]=i;
        }
    }
    /*** Find the parent of a node 'u'
    /*** Path Compression***/
    int find(int u){
        /*** Make the parent of the nodes in the path***/
        /***  from u--> parent[u] point to parent[u] ****/
        if (u!=parent[u]){
            parent[u]=find(parent[u]);
        }
        return parent[u];
    }
   /*** Union by rank**/
    void merge(int x,int y){
        x=find(x),y=find(y);
        /*** Make tree with smaller height  **/
        /***  a subtree of the other tree  **/
        if (rnk[x]>rnk[y]){
            parent[y]=x;
        }
        else{ /** If rnk[x] <= rnk[y]**/
            parent[x]=y;
        }
        if (rnk[x]==rnk[y]){
            rnk[y]++;
        }
    }
};
 /** Functions returns weight of the MST***/
int Graph::kruskalMST(){
    int mst_wt = 0; /*** Initialize result***/
    /*** Sort edges in increasing order on basis of cost***/
    sort(edges.begin(), edges.end());
    /*** Create disjoint sets***/
    DisjointSets ds(V);
    /*** Iterate through all sorted edges***/
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin();it!=edges.end();it++){
        int u=it->second.first;
        int v=it->second.second;
        int set_u=ds.find(u);
        int set_v=ds.find(v);
        /*** Check if the selected edge is creating***/
        /*** a cycle or not (Cycle is created if u***/
        /*** and v belong to same set)***/
        if (set_u!=set_v){
            /*** Current edge will be in the MST***/
            /*** so print it***/
            cout<<u<<"---"<<v<<endl;
            /*** Update MST weight***/
            mst_wt+=it->first;
            /*** Merge two sets***/
            ds.merge(set_u,set_v);
        }
    }
    return mst_wt;
}
/*** Driver program to test above functions***/
int main(){
    fstream fs,fp;
    fs.open("Input.txt",fstream::in);
    fp.open("Output.txt",fstream::out|fstream::trunc);
    char ch;             /***read a character**/
    int V,E;            /*** V means number of vertices in graph ;E means number of edges in graph**/
    int weight[100];       /***store number**/
    int src[100];       /***store start point**/
    int dest[100];      /****store end point**/
    string str;
    int k=0;            /****read file 算讀到edge的第幾行**/
    int n=0;            /****算同一行的第幾個字母**/
    char a[100]= {'\0'};    /****字母轉ascii code**/
    int start1,end1;            /****記A=0,B=1,C=2...**/
    while(fs>>V){
        if(V==0){
             return 0;
        }
        else{
            fs>>E;
            fs.get();
        for(int i=0;i<E;i++){
            fs.get(ch);
            while(ch!='\n'){
                if(ch!=' '){
                    str+=ch;
                }
                else if(ch==' '&& n==0){  /****start point***/
                    strcpy(a, str.c_str());     /***copy string to char array***/
                    start1 = int(a[0])-65;      /***A=0,B=1,C=2...***/
                    src[k]=start1;
                    n++;
                    str.clear();
                }
                else if(ch==' '&& n==1){  /***end point***/
                    strcpy(a, str.c_str());     /**copy string to char array***/
                    end1 = int(a[0])-65;        /***A=0,B=1,C=2...***/
                    dest[k]=end1;
                    str.clear();
                }
                fs.get(ch);
                if(fs.eof()){
                    break;
                }
            }
            weight[k]=atoi(str.c_str());  /***edge's weight***/
            k++;
            str.clear();
            n=0;
        }
        Graph r(V,E);
        for(int i=0;i<E;i++){
                r.addEdge(src[i],dest[i],weight[i]);;
        }
        int mst_wt=r.kruskalMST();
        fp<<mst_wt<<endl;
        k=0;
        }
    }
    fs.close();
    fp.close();
}
