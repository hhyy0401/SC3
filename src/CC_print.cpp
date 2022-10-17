#include "CC.h"
#include<vector>
#include<iostream>

void CC::print_sample(){
  
    for(int i=0; i<sample.size(); i++){
        cout<<i<<"-th sample: ";
        for(auto v:sample[i]){
            cout<<v<<"("<<color[v]<<")"<<" ";
        }
        cout<<endl;
    }
    return;
}

void CC::print_final_result(){
    for(int i=0; i<tot_motif; i++){
        if(simplicial_motifs[i]>0){
            cout<<i<<"-th simplicial motifs: "<<simplicial_motifs[i]<<endl;
        }
    }
}