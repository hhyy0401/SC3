# SC3: Simplet Counting Using Color Coding

These are source codes for the paper under review.


* **SC3** is the algorithm for counting simplets of size 4 and 5 based on Color Coding method where simplets are isomorphic classes of connected induced subcomplexes.
* **SC3**, which extends CC (Color Coding) method from graphlets to simplets, have following properties:
  1. accurate compared to baselines
  2. fast and scalable
* Especially, the counts of simplets by SC3 have strong power to characterize SCs domain by domain.



## Datasets 
1. Real world datasets are available in [here](https://www.cs.cornell.edu/~arb/data/). The format of the data is exactly as provided, and for CC, "{data}-nverts.txt", "{data}-simplices.txt" are only necessary. Feel free to delete repeated or non-maximal simplices.


  
## Outputs
1. (csv) timestamp for each step (building, sampling, scanning, matching) 
2. (csv) count of every simplet of size k with a format ({id of a simplet}, {counts}\n)


## Running Codes
1. command "bash run.sh". Feel free to change the variable k, s, trial, datas in "src>run.sh"
```
k="4 5" # a list of the size of simplets
ss="100 1000" #a list of the number of samples
datas="example" #a list of the name of datasets
trials=5 #the number of trials for running SC3.
```
