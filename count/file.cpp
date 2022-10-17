#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include<iostream>
#include"file.h"
#include<algorithm>

using namespace std;

File::File(string d){

    filepath="../dataset/";
    //proj="-proj-graph";

    filename_nv=filepath+d+"/"+d+"-nverts.txt";
    filename_sim=filepath+d+"/"+d+"-simplices.txt";
    //filename_proj=filepath+d+proj+"/"+d+proj+".txt";
    filename_time=filepath+d+"/"+d+"-times.txt";
}

void File::simplicial_list(double frac){ 
    if(frac!=1.0){get_time_standard(frac);}
    get_simplices_list();
    get_adjacency_list();
    return;
}


void File::get_time_standard(double frac){

    ifs4.open(filename_time);
    if(ifs4.is_open()){
        while(getline(ifs4, t)){
        time.push_back(stoll(t));
        tot_simplices++;}
    }
    ifs4.close();
    ts=time_standard(time, frac);
    return;
}

void File::get_simplices_list(){
    ifs.open(filename_nv); ifs2.open(filename_sim);
    int pointer=0;
    if(ifs.is_open() && ifs2.is_open()){
        int cnt = 0;
        while(getline(ifs, s)){
            num=stoi(s);
            vector<int> temp;
            for(int i=0; i<num; i++){
                getline(ifs2, s2);
                int num2=stoi(s2) - 1;
                if(V <= num2) V = num2 + 1;
                temp.push_back(num2);
            }
            sort(temp.begin(), temp.end());
            temp.erase(unique(temp.begin(),temp.end()),temp.end());

            if(ts!=-1){
                if(time[pointer]>ts) new_simplices.push_back(temp);
                else simplices.push_back(temp);
            }else simplices.push_back(temp);
            pointer++;
        }
    }
    ifs.close();  ifs2.close();
    return;
}

void File::get_adjacency_list(){
    vertex_to_simplices.resize(V);
    vertex_to_new_simplices.resize(V);
    int size=simplices.size();
    for(int i=0; i<size; i++){
        int l=simplices[i].size();
        for(int j=0; j<l; j++){
            vertex_to_simplices[simplices[i][j]].push_back(i);
        }
        projected_graph(i);
    }
    for(int i=0; i<V; i++){
        sort(old_Adj[i].begin(), old_Adj[i].end());
        old_Adj[i].erase(unique(old_Adj[i].begin(), old_Adj[i].end()), old_Adj[i].end());
    }
    if(ts!=-1){
        size=new_simplices.size();
        for(int i=0; i<size; i++){
            int l=new_simplices[i].size();
            for(int j=0; j<l; j++){
                vertex_to_new_simplices[new_simplices[i][j]].push_back(i);
            }
        }
    }
    return;
}

void File::projected_graph(int idx){
    old_Adj.resize(V);
    int size=simplices[idx].size();
    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            if(simplices[idx][i] != simplices[idx][j]){
                addEdge(&old_Adj, simplices[idx][i], simplices[idx][j]);
            }else{
                cout << "REALSTORY?" << endl;
            }
        }
    }

}

void File::print_simplicies(){
    for(int i=0; i<simplices.size(); i++){
        for(int j=0; j<simplices[i].size(); j++){
            cout<<simplices[i][j]<<" ";
        }
        cout<<endl;
    }
}

void File::print_edges(){
    for(int i=0; i<edges.size(); i++){
        for(int j=0; j<edges[i].size(); j++){
            cout<<edges[i][j]<<" ";
        }
        cout<<endl;
    }
}

long long File::time_standard(vector<long long> temp, double frac){
    sort(temp.begin(), temp.end());
    int idx=(int)tot_simplices*frac;
    int max=temp.size()-1;
    if (idx>max) idx=max;
    return temp[idx];
}

void File::addEdge(vector<vector<int>> *adj, int u, int v){
    (*adj)[u].push_back(v);
    (*adj)[v].push_back(u);
}


void File::print_graph(vector<vector<int>> adj, int V){
    for (int v =0; v < V; ++v) {
        cout << "vertex " << v+1 << " ";
        for (auto x : adj[v])
            cout << "-> " << x;
        cout<<endl;
    }
}

/*
void File::weighted_edge_list(){
    tot_Adj.resize(V);
    ifs3.open(filename_proj);
    if(ifs3.is_open()){
        while(getline(ifs3, s)){
            istringstream ss(s);
            vector<int> temp;
            while(getline(ss, s, ' ')){                
                temp.push_back(stoi(s));        
            } 
            edges.push_back(temp);
            addEdge(&tot_Adj, temp[0], temp[1]);
            if(V<temp[1]){V=temp[1];}
        }
    }
    ifs3.close();  
    return;
}*/