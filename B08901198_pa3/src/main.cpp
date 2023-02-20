#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
//void MaxHeapify(vector<edge> data, int root,int heapSize);
//void BuildMaxHeap(vector<edge> data ,int heapSize);
class edge{
    public:
       int u;
       int v;
       int weight;
       void info(int s,int e,int w){
           u=s;
           v=e;
           weight=w;
        };

};
void MaxHeapify(vector<edge>& data, int root,int heapSize);
void BuildMaxHeap(vector<edge>& data ,int heapSize);

void HeapSort(vector<edge>& data) {
    // Build Max-Heap
    int heapSize=data.size();
    BuildMaxHeap(data,heapSize);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0,heapSize);
    }
}

void MaxHeapify(vector<edge>& data, int root,int heapSize) {
    int l_child;
    int r_child;
    l_child=2*(root+1)-1;
    r_child=2*(root+1); 
    int max=root;
    if (l_child <= heapSize-1 && data[l_child].weight>data[root].weight){
            max=l_child;}
    if(r_child <= heapSize-1 && data[r_child].weight>data[max].weight){
            max=r_child;
    }
    if(max!=root){
        swap(data[root],data[max]);
        MaxHeapify(data,max,heapSize);
    }
}

void BuildMaxHeap(vector<edge>& data ,int heapSize) { 
    for(int i =(data.size()/2)-1;i>=0;i--){
        MaxHeapify(data,i,heapSize);
    }


}
void makeset(vector<int>& parent,vector<int>& rank , int u){
    parent[u]=u;
    rank[u]=0;

}

int findset(vector<int>& parent ,int u){
    if(u!=parent[u]){
        parent[u]=findset(parent,parent[u]);
    }
    return parent[u];


}
void link(vector<int> &parent,vector<int> &rank,int u ,int v){
    if(rank[u]>rank[v]){
        parent[v]=u;
    }
    else{
        parent[u]=v;
        if(rank[u]==rank[v]){
            rank[v]=rank[v]+1;
        }
    }

}
int Kruskal(vector<edge> &edges,int vertices ,vector<vector<int>> &result){
    HeapSort(edges);
    vector<int> parent;
    vector<int> rank;
    int count=0;
    int count_edge=0;
    rank=vector<int>(vertices,-1);
    parent=vector<int>(vertices,-1);
    for(int i=0;i<vertices;i++){
        makeset(parent,rank,i);
    }
    for(int i=0;i<vertices;i++){
        //cout<<parent[i];
    }
    int m=edges.size();
    for(int i =m-1;i>=0;i--){
        //cout<<i;
        int u=edges[i].u;
        int v=edges[i].v;
        //cout<<u<<" "<<v<<" "<<edges[i].weight<<endl;
        //cout<<findset(parent,u)<<" "<<findset(parent,v)<<endl;
        if (findset(parent,u)==findset(parent,v)){
            //cout<<edges[i].u<<" "<<edges[i].v<<" "<<edges[i].weight<<endl;
            count+=edges[i].weight;
            result.push_back({edges[i].u,edges[i].v,edges[i].weight});

        }
        else{
            count_edge++;
            link(parent,rank,findset(parent,u),findset(parent,v));
        }


    }
    return count;


}

void print_cycle(vector<int> parent,vector<int> &circle,int u, int v){
    circle.push_back(u);
    if(parent[u] != v){
        print_cycle(parent,circle,parent[u],v);
    }
    else{
        circle.push_back(v);
    }


}
vector<int> DFSvisit(vector<int> &d_time,vector<int> &f_time,vector<int> &parent,vector<string> &color,vector<int> &circle,vector<vector<int>> adj,int u,int &time){
    time++;
    d_time[u]=time;
    color[u]="gray";
    vector<int> u_adj=adj[u];
    for(int i=0;i<u_adj.size();i++){
        int v=u_adj[i];
        if(color[v]=="white"){
            parent[v]=u;
            //cout<<u<<" visit "<<v;
            return DFSvisit(d_time,f_time,parent,color,circle,adj,v,time);
        }
        else if(color[v]=="gray"  ){
            //cout<<"check cycle";
            print_cycle(parent,circle,u,v);
            return circle;
        }
    }
    
    color[u]="black";
    time++;
    f_time[u]=time;
    return {};
}

vector<int> DFS(vector<int> &d_time,vector<int> &f_time ,vector<int> &parent,vector<string> &color,vector<vector<int>> adj,int &time){
    //cout<<"DFS";
    vector<int> circle={};
    int vertices=d_time.size();
    //cout<<vertices;
    for(int u=0;u<vertices;u++){
        if(color[u]=="white"){
            return DFSvisit(d_time,f_time,parent,color,circle,adj,u,time);
        }
    }
    return {};

}

int  transitive(vector<edge> edges,int vertices,vector<vector<int>> &result){
    HeapSort(edges);
    vector<vector<int>> adj;
    //vector<vector<int>> count_e;
    adj=vector<vector<int>>(vertices,vector<int>{});
    vector<vector<int>> count_e(vertices,vector<int>(vertices,-101));
    int count=0;
    int count_edge=0;
    int m=edges.size();
    int check=0;

    for(int i=0;i<edges.size();i++){
        adj[edges[i].u].push_back(edges[i].v);
        count_e[edges[i].u][edges[i].v]=edges[i].weight;
    }
    vector<int> circle={-1};
    while(circle.size()>0){
        //cout<<"check"<<endl;
        circle.clear();
        vector<string> color(vertices,"white");
        vector<int> d_time(vertices,-1);
        vector<int> f_time(vertices,-1);
        vector<int> parent(vertices,-1);
        //bool cycle=false;
        int time=0;
        circle=DFS(d_time,f_time,parent,color,adj,time);
        //cout<<"circle insert";
        
        int min=101;
        int min_u=-1;
        int min_v=-1;
        if(circle.size()!=0){
            //cout<<"check start";
            circle.push_back(circle[0]);
            for(int i=0;i<circle.size()-1;i++){
                int u=circle[i+1];
            //    cout<<"check u";
                int v=circle[i];
            //    cout<<"check v";
                if(count_e[u][v]<min){
                   min=count_e[u][v];
                   min_u=u;
                   min_v=v;
            //       cout<<"check min";
                }
            }
            //cout<<circle.size()<<"circle size"<<endl;
            //cout<<min_u<<" "<<min_v<<endl;
            count+=count_e[min_u][min_v];
            result.push_back({min_u,min_v,count_e[min_u][min_v]});
            count_e[min_u][min_v]=-101;
            vector<int>::iterator k=find(adj[min_u].begin(),adj[min_u].end(),min_v);
            int index=distance(adj[min_u].begin(),k);
            adj[min_u].erase(adj[min_u].begin()+index);
            //cout<<(circle.size()>0)<<endl;
        }
    //cout<<(circle.size()>0)<<endl;
    }
    return count;

}



int main(int argc,char* argv[]){
    //cout<<"main";

    fstream fin(argv[1]);
    fstream fout;
    //fin.open(argv[1],ios::in);
    fout.open(argv[2],ios::out);
    int v;
    int e;
    string graph_type;
    fin >> graph_type;
    fin >> v;
    fin >> e;
    //gcout<<v<<endl;
    int a,b,c;
    vector<edge> edges;
    while(fin >> a >> b >>c){
        edge ed;
        ed.info(a,b,c);
        //cout<<a<<b<<c<<endl;
        edges.push_back(ed);
    };
    if(graph_type=="u"){
        vector<vector<int>> result={};
        fout<<Kruskal(edges,v,result)<<endl;
        for(int i=0;i<result.size();i++){
            for(int j=0;j<result[i].size();j++){
                fout<<result[i][j]<<" ";
            }
            fout<<endl;
        }
    }
    else{
        //cout<<"check";
        vector<vector<int>> result={};
        fout<<transitive(edges,v,result)<<endl;
        for(int i=0;i<result.size();i++){
            for(int j=0;j<result[i].size();j++){
                fout<<result[i][j]<<" ";
            }
            fout<<endl;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
