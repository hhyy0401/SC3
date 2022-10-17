#include "CC.h"
#include<vector>
#include<iostream>
#include<map>
#include<algorithm>
#include<math.h>
#include<fstream>
#include<string>
#include<iterator>
#include<sstream>
#include<set>
#include<cmath>

void CC::find_motifs(int s, int w){
    this->weight=w;
    vector<int> base;
    for(int i=0; i<k; i++) base.push_back(i);
    int perm_cnt = 0; 
    do{
        permuted_code.push_back(vector<int>(1 << k, 0));
        for(int j=0;j<(1 << k);j++){
            for(int digit=0;digit<5;digit++){
                if(j & (1 << digit)) permuted_code[perm_cnt][j] += (1 << base[digit]);
            }
        }
        perm_cnt += 1;
    }while (next_permutation(base.begin(), base.end()));
    //1.save number of spanning tree
    save_spannings_density();
    save_motifs();
    final_motifs(s);
    return;
}

void CC::final_motifs(int s){
    //vector<double> temp;
    vector<count_type> temp;
    //cout << "n_simplets: " << n_simplets << endl;
    temp.resize(n_simplets, 0);
    simplets.resize(n_simplets, 0);
    //double all_simplets=0.0;
    double p=((double)factorial(k))/pow(k, k);
    for(int i=0; i<s; i++){
        count_type w = 1;
        // double w = 1;
        int hashed_code = 0;
        for(auto &it: maximal_simplices[i]){
            hashed_code += (1 << (it.first - 1));
            if(weight==1) w*=it.second;
        }
 
        int answer = hash[hashed_code];
        temp[answer]+= w;
        //all_simplets += w;
    }
    for(int i=0; i<n_simplets; i++){
        //simplets[i] = ((double)rng_root.back()) * (temp[i]/(double)all_simplets) / (spanning_cnts[i] * p);
        simplets[i] = (rng_root.back() / p) * (temp[i] / (double)spanning_cnts[i]) / (double)s;
        //cout << "NEW: " << i << " " << simplets[i] << endl;
    }
    return;
}

void CC::save_spannings_density(){
    num_spanning.clear();
    density.clear();

    ifstream ifs; string s;
    ifs.open("../motif/spanning_"+to_string(k)+".txt");
    ifstream ifs2; string s2;
    ifs2.open("../motif/density_"+to_string(k)+".csv");
    if(ifs.is_open() && ifs2.is_open()){
        while(getline(ifs, s)){
            num_spanning.push_back(stoi(s));
        }
        if(getline(ifs2, s2)){
            istringstream ss(s2);
            string stringBuffer; 
            while(getline(ss,stringBuffer,',')){density.push_back(stod(stringBuffer));}
        }
    }
    ifs.close(); ifs2.close();
    return;
}



void CC::save_motifs(){
    ifstream ifsm; string sm;
    ifstream ifse; string se;
    ifstream ifsv; string sv;
    ifstream ifsk; string sk;
    ifsm.open("../motif/nummotifs_"+to_string(k)+".txt");
    ifse.open("../motif/numedges_"+to_string(k)+".txt");
    ifsk.open("../motif/key_"+to_string(k)+".txt");
    ifsv.open("../motif/value_"+to_string(k)+".txt");
    string s; 
    int zero=int('0');
    int perm_cnt = (int)permuted_code.size();
    n_simplets = 0;
    int gmotif_idx = 0;

    spanning_cnts.clear();
    vector<int> closed;
    //cout << "perm_cnt: " << perm_cnt << endl;
    if(ifsm.is_open() && ifse.is_open() && ifsv.is_open() && ifsk.is_open()){
        while(getline(ifsm, sm)){ // number of motifs
            int sm_size=stoi(sm); 
            for(int i=0; i<sm_size; i++){ //for each graph-motif 
                if(getline(ifse, se)){ //number of edges in each motifs
                    int se_size=stoi(se);
                    closed.clear();
                    for(int j=0; j<se_size; j++){
                        if(getline(ifsv, sv) && getline(ifsk, sk)){
                            int raw_key = stoi(sk), raw_value = stoi(sv);
                            if(raw_value > 0){
                                int simplex_code = 0;
                                while(raw_key){
                                    simplex_code += (1 << ((raw_key % 10) - 1));
                                    raw_key /= 10;
                                }
                                closed.push_back(simplex_code);
                            }
                        }
                    }
                    for(int i=0;i<perm_cnt;i++){
                        int hashed = 0;
                        for(auto &c_simplex: closed){
                            hashed |= (1 << (permuted_code[i][c_simplex] - 1));
                        }
                        hash[hashed] = n_simplets;
                    }
                    spanning_cnts.push_back(num_spanning[gmotif_idx]);
                }
                n_simplets += 1;
            }
            gmotif_idx += 1;
        }
    }
    ifsm.close();
    ifse.close();
    ifsv.close();
    ifsk.close();
    return;
}


int CC::factorial(int n){
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}