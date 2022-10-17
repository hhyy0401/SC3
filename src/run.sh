make clean
make main

ks="4" #4 or 5
ss="100 1000"
trial=5

datas="coauth-DBLP coauth-MAG-Geology coauth-MAG-History congress-bills contact-high-school contact-primary-school DAWN email-Enron email-Eu NDC-classes NDC-substances tags-ask-ubuntu tags-math-sx tags-stack-overflow threads-ask-ubuntu threads-math-sx threads-stack-overflow"

echo "START"

for k in ${ks[@]}
do
    for data in ${datas[@]}
    do
        echo "k="${k}
        for s in ${ss[@]}
        do
            echo "data="${data} "sample="${s}
            OMP_NUM_THREADS=6 ./main ${k} ${s} ${trial} ${data}
        done
    done
done

echo "END"