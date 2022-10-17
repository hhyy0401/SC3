# SC3: Simplet Counting Using Color Coding

These are source codes for the paper under review.


* **SC3** is the algorithm for counting simplets of size 4 and 5 based on Color Coding method where simplets are isomorphic classes of connected induced subcomplexes.
* **SC3**, which extends CC (Color Coding) method from graphlets to simplets, have following properties:
  1. accurate compare to baseline
  2. fast and scalable
* Especially, the counts of simplets by SC3 have strong power to characterize networks domain by domain.



## Datasets 
1. Real world datasets are available in [here](https://www.cs.cornell.edu/~arb/data/). 
  
## Outputs
1. timestamp for each step (building, sampling, scanning, matching)
2. count of every simplet of size k


## Running Codes
1. create folders (dataset, result) to the parallel directory of "src".
2. create folders (timestamp, CC) on a subdirectory of "result".
3. command "bash run.sh"  
