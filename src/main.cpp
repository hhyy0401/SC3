#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<set>
#include<time.h>
#include<omp.h>

#include "file.h"
#include "CC.h"

using namespace std;

int main(int argc, char **argv){

    int k=atoi(argv[1]); //k=4,5
    int s=atoi(argv[2]); //s: sample size
    
    int w=0;
    double frac=1.0;

    int tries=atoi(argv[3]); 
    string data=argv[4];


    double duration;
    double start=clock();
    double start2=omp_get_wtime();

    
    ofstream myfile;
    myfile.open("../result/timestamp/timestamp_"+data+"_k"+to_string(k)+"_s"+to_string(s)+"_w"+to_string(w)+"_f"+to_string((int)(frac*100))+".csv"); 

    File file(data);

    vector<vector<int>> Adj_list;

    file.simplicial_list(frac);

    Adj_list=file.old_Adj; 
    //cout<<file.V<<endl;
    // file.print_graph(Adj_list, file.V); //
    //file.print_simplicies();
    
    myfile<<"reading,"<<(double)(clock()-start)/CLOCKS_PER_SEC<<"\n";
    //cout<<"  ===reading==="<<endl;
    start=clock();

    
    for(int i=0; i<tries; i++){
        //myfile<<"try,"<<i<<"\n";
        cout<<"try: "<<i<<endl;
        // make table
        start=clock(); start2 = omp_get_wtime(); 
        CC cc(k, file.V);
        
        cc.build(Adj_list); 
        //cout<<"building,"<<(double)(clock()-start)/CLOCKS_PER_SEC << " omptime " << (omp_get_wtime() - start2) << "\n";

        myfile<<"building,"<< (omp_get_wtime() - start2) << "\n";
        //cout<<"  ===building==="<<endl;

        //sampling
        start=clock(); start2=omp_get_wtime();
        cc.sampling(s);
        //cout<<"sampling,"<<(double)(clock()-start)/CLOCKS_PER_SEC << " omptime " << (omp_get_wtime() - start2) << "\n";
        myfile<<"sampling,"<< (omp_get_wtime() - start2) << "\n";
        //cout<<"  ===sampling==="<<endl;
        
        start=clock(); start2=omp_get_wtime();
        cc.scan(file.simplices, file.vertex_to_simplices, s);
        
        //cout<<"scanning,"<<(double)(clock()-start)/CLOCKS_PER_SEC << " omptime " << (omp_get_wtime() - start2) << "\n";
        myfile << "scaning,"<< (omp_get_wtime() - start2) << "\n";
        //cout<<"  ===scaning==="<<endl;

        start=clock(); start2=omp_get_wtime();
        cc.find_motifs(s, w);
        //cout<<"matching,"<<(double)(clock()-start)/CLOCKS_PER_SEC << " omptime " << (omp_get_wtime() - start2) << "\n";
        myfile<<"matching,"<< (omp_get_wtime() - start2) << "\n";
        //cout<<"  ==matching=="<<endl;


        //cc.print_final_result()
        cc.save_result(s, i, frac, data);
    } 
    myfile.close();
        
    return 0;
}