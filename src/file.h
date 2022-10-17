#ifndef FILE_H
#define FILE_H

#include<fstream>
#include<vector>
#include<string>

using namespace std;

class File {

    string filepath, filename_nv, filename_sim, filename_proj, filename_time; string proj;
    string txt;
    ifstream ifs; ifstream ifs2; ifstream ifs3; ifstream ifs4;
    

    int num; 
    string s; string s2; string t;

    long long time_standard(vector<long long> temp, double frac);
    int tot_simplices=0;
    long long ts=-1;

    void get_time_standard(double frac);
    void get_simplices_list();
    void get_adjacency_list();
    void projected_graph(int i);
    void addEdge(vector<vector<int>> *adj, int u, int v);
    
    public: 
        File(string d);
        void simplicial_list(double frac);
        //void weighted_edge_list();
        int V=0; 
        vector<vector<int>> simplices;
        vector<vector<int>> new_simplices;

        vector<vector<int>> vertex_to_simplices;
        vector<vector<int>> vertex_to_new_simplices;
        
        vector<vector<int>> old_Adj;
        vector<vector<int>> tot_Adj;
        vector<vector<int>> edges;
        vector<long long> time;

        void print_simplicies();
        void print_edges();
        void print_graph(vector<vector<int>> adj, int V);
};

#endif


