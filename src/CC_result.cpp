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

void CC::save_result(int s, int trial, double frac, string task){
    string filename;
    if (trial==0) filename="../result/CC/"+task+"_k"+to_string(k)+"_s"+to_string(s)+"_w"+to_string(weight)+"_f"+to_string((int)(frac*100))+".csv";
    else if(trial>0) filename="../result/CC/"+task+"_k"+to_string(k)+"_s"+to_string(s)+"_w"+to_string(weight)+"_f"+to_string((int)(frac*100))+"("+to_string(trial)+")"+".csv";
    fstream file_out;
    file_out.open(filename, ios_base::out);
    if (!file_out.is_open()) {
        cout << "failed to open " << filename << '\n';
    } else {
        file_out<<"simplicial_motif_index, count"<<endl; //closure
        for(int i=0; i<n_simplets; i++){
            double y=simplets[i];
            if(y>0){
                file_out<<i<<","<<to_string(simplets[i])<<endl;
            }
        }

        //cout << "END" << endl;
    }

    file_out.close();

    return;
}