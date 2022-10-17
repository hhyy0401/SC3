#include "CC.h"
#include<vector>
#include<iostream>
#include<map>
#include<set>
#include<algorithm>
#include<math.h>
#include<time.h>
#include<omp.h>

void CC::scan(vector<vector<int>>& simplices, vector<vector<int>>& vertex_to_simplices, int s){
    maximal_simplices.resize(s);
    vector< vector<int> > seen_vertices, seen_simplices, intersect_counts;
    int n_threads = omp_get_max_threads();
    //cout << "n_threads: " << n_threads << endl;

    seen_vertices.resize(n_threads); seen_simplices.resize(n_threads); intersect_counts.resize(s);
    for(int i=0;i<n_threads;i++){
        seen_vertices[i].resize((int)vertex_to_simplices.size());
        seen_simplices[i].resize((int)simplices.size());
    }
    for(int i=0;i<s;i++){
        intersect_counts[i].resize((1 << k));
    }
    //cout << "n_nodes: " << ((int)(vertex_to_simplices.size())) << ", n_simplices: " << (int)simplices.size() << endl;

    #pragma omp parallel for
    for(int i=0; i<s; i++){
        int tid = omp_get_thread_num();
        for(int j=0;j<k;j++){
            seen_vertices[tid][sample[i][j]] = (1 << j);
        }
        for(auto &v: sample[i]){
            for (auto &sid: vertex_to_simplices[v]) {
                if(seen_simplices[tid][sid] == i+1) continue;
                seen_simplices[tid][sid] = i+1;
                int intersect_state = 0;
                for(auto &u: simplices[sid]){
                    intersect_state |= seen_vertices[tid][u];
                }
                if(num_ones[intersect_state] >= 2){
                    intersect_counts[i][intersect_state] += 1;
                }
            }
        }
        for(int j=0;j<k;j++){
            seen_vertices[tid][sample[i][j]] = 0;
        }
        bool leaked = true;
        for(int j=0;j<(1 << k);j++){
            if(intersect_counts[0][j] > 0){
                leaked = false;
                break;
            }
        }
    }
    //cout << "Phase 1 end" << endl;
    for(int i=0; i<s; i++){
        for(int j=(1 << k)-1;j>=0;j--){
            if(intersect_counts[i][j] > 0){
                maximal_simplices[i].push_back({j, intersect_counts[i][j]});
                for(int jj = 0; jj < j; jj++){
                    if((j & jj) == jj) intersect_counts[i][jj] = 0;
                }
            }
        }
    }
    //cout << "Phase 2 end" << endl;
}

