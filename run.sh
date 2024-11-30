echo $1

outputFile=ParallelMatrixTransposition.pbs

cat >$outputFile <<EOL
#!/bin/bash
# Job name
#PBS -N ParallelMatrixTransposition
# Output files
#PBS -o ./ParallelMatrixTransposition.o
#PBS -e ./ParallelMatrixTransposition.e
# Queue name
#PBS -q short_cpuQ
# Set the maximum wall time
#PBS -l walltime=0:10:00
# Number of nodes, cpus, mpi processors and amount of memory
#PBS -l select=1:ncpus=64:ompthreads=64:mem=1mb

# Modules for C
module load gcc91
g++() {
    g++-9.1.0 "\$@"
}
g++ --version
# Select the working directory
cd $1

# The code should be compiled before submitting the job  \n
make run
git checkout O1
make run
git checkout O2
make run
git checkout loopUnroll
make run
git checkout vectorization
make run
git checkout vectorization_loopUnroll
make run
git checkout OMP_staticScheduling
make run
git checkout OMP_dynamicScheduling
make run
git checkout OMP_guidedScheduling
make run

# Run code
./bin/run/main.out -m 4 -M 12
./bin/run/O1.out -m 4 -M 12
./bin/run/O2.out -m 4 -M 12
./bin/run/loopUnroll.out -m 4 -M 12
./bin/run/vectorization.out -m 4 -M 12
./bin/run/vectorization_loopUnroll.out -m 4 -M 12
./bin/run/staticScheduling.out -m 4 -M 12
./bin/run/dynamicScheduling.out -m 4 -M 12
./bin/run/guidedScheduling.out -m 4 -M 12
EOL