#!/bin/bash

if [ "$#" -ne "2" ];
then 
    echo "Usage: ./generate_benchmarks.sh MAX_ITERATIONS STEP"
    exit 1
fi

mkdir -p stats

echo "Generating benchmarks for OpenMP ..."

cd OpenMP
make SILENT=1
touch ../stats/OpenMP.csv

echo "iterations;sequential;parallel" > ../stats/OpenMP.csv

for ((i=$2; i <= $1; i+=$2))
do
    seq=$(./omp -s $i)
    par=$(./omp -p $i)
    echo "$i;$seq;$par" >> ../stats/OpenMP.csv
done

make clean SILENT=1

echo "Generating benchmarks for OpenCL ..."

cd ../OpenCL
make SILENT=1
touch ../stats/OpenCL.csv

echo "iterations;sequential;parallel" > ../stats/OpenCL.csv

for ((i=$2; i <= $1; i+=$2))
do
    seq=$(./ocl -s $i)
    par=$(./ocl -p $i)
    echo "$i;$seq;$par" >> ../stats/OpenCL.csv
done

make clean SILENT=1

echo "Generating benchmarks for Python ..."

cd ../Python 
touch ../stats/Python.csv
echo "iterations;sequential;parallel" > ../stats/Python.csv

for ((i=$2; i <= $1; i+=$2))
do
    seq=$(python3 hello_world.py -s $i)
    par=$(python3 hello_world.py -p $i)
    echo "$i;$seq;$par" >> ../stats/Python.csv
done

exit 0