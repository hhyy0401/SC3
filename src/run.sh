make clean
make main

ks="4 5" #4 or 5
ss="10000"
trial=5

datas="example"

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