#!/bin/bash

if [ "$#" -ne "2" ];
then 
    echo "Usage: ./generate_benchmarks.sh MAX_ITERATIONS STEP"
    exit 1
fi

echo "Generating benchmarks for OpenMP ..."

cd OpenMP
make SILENT=1
touch ../stats/OpenMPSEQ.csv
touch ../stats/OpenMPPAR.csv

for ((i=$2; i <= $1; i+=$2))
do
    ./omp -s $i >> ../stats/OpenMPSEQ.csv
    ./omp -p $i >> ../stats/OpenMPPAR.csv
done

make clean SILENT=1

echo "Generating benchmarks for OpenCL ..."

cd ../OpenCL
make SILENT=1
touch ../stats/OpenCLSEQ.csv
touch ../stats/OpenCLPAR.csv

for ((i=$2; i <= $1; i+=$2))
do
    ./ocl -s $i >> ../stats/OpenCLSEQ.csv
    ./ocl -p $i >> ../stats/OpenCLPAR.csv
done

make clean SILENT=1

echo "Generating benchmarks for Python ..."

cd ../Python 
touch ../stats/PythonSEQ.csv
touch ../stats/PythonPAR.csv

for ((i=$2; i <= $1; i+=$2))
do
    python3 hello_world.py -s $i >> ../stats/PythonSEQ.csv
    python3 hello_world.py -p $i >> ../stats/PythonPAR.csv
done

exit 0