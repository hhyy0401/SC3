# SC3: Simplet Counting Using Color Coding

These are source codes for the paper "Characterization of Simplicial Complexes by Counting Simplets Beyond Four Nodes".


* **SC3** is the algorithm for counting simplets of size 4 and 5 based on Color Coding method where simplets are isomorphic classes of connected induced subcomplexes.
* **SC3**, which extends CC (Color Coding) method from graphlets to simplets, have following properties:
  1. accurate compared to baselines
  2. fast and scalable
* Especially, the counts of simplets by SC3 have strong power to characterize SCs domain by domain.



## Datasets 
1. Real world datasets are available [here](https://www.cs.cornell.edu/~arb/data/). The format of the data is exactly as provided, and for SC3, only "{data}-nverts.txt" and "{data}-simplices.txt" are necessary.
2. [Statistics of datasets we used]

| dataset  | # of vertices | # of maximal simplices |
|----|---:|---:|
| coauth-DBLP | 1,924,991 | 1,730,664 |
| coauth-MAG-Geology | 1,256,385 | 925,027 |
| coauth-MAG-History | 1,014,734 | 774,495 |
| congress-bills  | 1,718 | 48,898 |
| contact-high-school | 327 | 4,862 |
| contact-primary-school | 242 | 8,010 |
| DAWN  | 2,558 | 72,421 |
| email-Eu | 998 | 8,102 |
| email-Enron | 143 |433 |
| NDC-classes | 1,161 | 563 |
| NDC-substances | 5,311 | 6,555 |
| tags-ask-ubuntu | 3,029 | 95,639 |
| tags-stak-overflow  | 49,998 |3,781,574 |
| threads-ask-ubuntu |125,602 | 149,025 |
| threads-math-sx  |  176,445 | 519,573  |
| threads-stack-overflow  |  2,675,955 |  8,694,667 |
  
## Outputs
1. (csv) timestamp for each step (building, sampling, scanning, matching) 
2. (csv) count of every simplet of size k with a format ({id of a simplet}, {counts}\n)


## Running Codes
1. command "bash run.sh". Feel free to change the variable **k, ss, trials, datas** in the file "run.sh"
```
k="4 5" # a list of the size of simplets
ss="100 1000" #a list of the number of samples
datas="example" #a list of the name of datasets
trials=5 #the number of trials for running SC3.
```
