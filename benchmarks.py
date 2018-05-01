from subprocess import Popen, PIPE
from multiprocessing import Pool
import os

def compute_benchs(cmd, iterations, step, accuracy_repetitions=8):
    benchs = {}
    for repetition in range(1, accuracy_repetitions):
        # CAN BE PARALLELIZED !!!
        for step_iterations in range(step, iterations + step, step):
            seq = int(os.popen('{0} -s {1}'.format(cmd, step_iterations)).read())
            par = int(os.popen('{0} -p {1}'.format(cmd, step_iterations)).read())

            if step_iterations in benchs:
                seq = (seq + benchs[step_iterations]['seq']) / 2
                par = (par + benchs[step_iterations]['par']) / 2

            benchs[step_iterations] = {
                'par': par,
                'seq': seq
            }
            
    return benchs

def echo_benchs(benchs, output):
    with open(output, 'w+') as out:
        out.write('iterations;sequential;parallel\n')
        for step, records in benchs.items():
            out.write('{0};{1};{2}\n'.format(step, records['seq'], 
                                             records['par']))
        out.close()

def generate_benchmarks(args):
    print('Generating benchmarks for {0} ...'.format(args[4]))

    os.system('mkdir -p stats')
    os.system('touch stats/{0}.csv'.format(args[4]))
    
    iterations = int(args[1])
    step = int(args[2])
    cmd = args[3]

    benchs = compute_benchs(cmd, iterations, step)

    echo_benchs(benchs, 'stats/{0}.csv'.format(args[4]))

if __name__ == '__main__':

    if len(os.sys.argv) != 5:
        print('Usage: python benchmarks.py MAX_ITERATIONS STEP CMD OUTPUT')
        exit(1)

    generate_benchmarks(os.sys.argv)
