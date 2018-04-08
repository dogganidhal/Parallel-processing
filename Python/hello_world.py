
import sys
import time
import argparse
from multiprocessing import Pool
from enum import Enum

class TimeUnit(Enum):
    
    MICROSECONDS = 0
    MILLISECONDS = 1
    SECONDS = 2

def sum_for_index(index):
    sum = 0
    for i in range(index):
        sum += i
    return sum

def measure_time(func, unit):
    begin = time.time()
    func()
    end = time.time()
    if unit == TimeUnit.MICROSECONDS:
        return (end - begin) * 1000000
    elif unit == TimeUnit.MILLISECONDS:
        return (end - begin) * 1000
    return end - begin

def sum_for_range(r):
    for i in r:
        sum_for_index(i)

def compute_sequentially(iterations):
    return measure_time(lambda: sum_for_range(range(0, iterations)), TimeUnit.MILLISECONDS)

def compute_concurrently(iterations):
    pool = Pool(processes=16)
    return measure_time(lambda: pool.map(sum_for_index, range(0, iterations)), TimeUnit.MILLISECONDS)

if __name__ == '__main__':

    if len(sys.argv) != 3:
        print("Usage: python -[p|s] iterations")
        exit(1)

    t = 0
    if sys.argv[1] == "-s":
        t = compute_sequentially(int(sys.argv[2]))
    elif sys.argv[1] == "-p":
        t = compute_concurrently(int(sys.argv[2]))
    else:
        print("Usage: python -[p|s] iterations")
        exit(1)

    print("time elapsed {0}\n".format(int(t)))