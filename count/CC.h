#ifndef CC_H
#define CC_H
#include<string>
#include<vector>
#include<map>
#include<tuple>
#include<set>
#include<math.h>
#include<unordered_map>
#include <atomic>
#include <queue>

using namespace std;
using count_type = __int128_t;
//using count_type = long long;

class CC {
    struct decomp_type{
        int num_nodes, main_id, sub_id, deg_root;
    };
    struct queue_type{
        int v, treelet_id, colors;
    };
    struct rng_type{
        struct info_type{
            int main_tid, main_colors, sub_v, sub_tid, sub_colors;
        };
        int capacity;
        vector<info_type> infos;
        vector<count_type> cumcnts;
    };
    int k; 
    int V; 
    
    count_type total_treelet=0;
    
    vector< vector<decomp_type> > D;
    
    int sum=0;
    int colors;
    int weight;    
    vector<vector<int>> adj_list;

    int num[5]={1, 1, 2, 4, 9}; //number of rooted trees of n nodes
    int diff[5]={0, 0, 0, 1, 4}; // cumul-i
    int cumul[5]={0,1,2,4,8}; //for tree 17-> (4, 9)
    
    vector<int> num_ones;
    vector< vector<int> > bin_ones;
    vector<int> color_idx;

    vector< vector< vector<count_type> > > C;
    vector< vector< vector<rng_type> > > memoized_rng;
    vector< vector<queue_type> > ques;

    void create_tree_table();
    void update(int v, int treelet_id); 
    vector< vector< vector< pair<int, int> > > > color_pairs;
    vector<int> color;

    //sample
    vector<count_type> rng_root;

    void iterative_sample(int t);    
    void sample_treelet(int idx);

    vector< vector<int> > sample;

    //scan
    vector< vector< pair<int, int> > > maximal_simplices;
    
    //motif
    int factorial(int n);
    vector<int> num_spanning; vector<double> density;

    vector<vector<int>> permuted_code;
    int tot_motif=0;
    int n_simplets=0;
    
    unordered_map<int, int> hash;
    vector<int> spanning_cnts;

    count_type normalize_constant=0;

    
    void save_spannings_density();
    void save_motifs();
    void final_motifs(int s);
    
    public:
        CC(int K, int V);
        void build(vector<vector<int>> adj_list);
        void sampling(int s);
        void print_sample();
        void scan(vector<vector <int>> &simplicies, vector<vector<int>> &vertex_to_simplices, int s);
        void find_motifs(int s, int w);
        void print_gmotifs();
        void print_hashkey();
        void print_final_result();
        void save_result(int s, int trial, double frac, string task);

        vector<float> simplicial_motifs;
        vector<double> simplets;

};

#endif    