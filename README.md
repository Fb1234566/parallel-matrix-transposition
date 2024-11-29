# Parallel Matrix Transposition
This program performs parallel transposition of matrices. Below are the instructions to build and run the program.

## Index
- [Repository Structure](#repository-structure)
  - [Main Branch](#main-branch)
  - [LoopUnroll Branch](#loopunroll-branch)
  - [Vectorization Branch](#vectorization-branch)
  - [Vectorization_loopUnroll Branch](#vectorization_loopunroll-branch)
- [Build Instructions](#build-instructions)
- [Execution Instructions](#execution-instructions)
    - [Examples](#examples)
    - [Expected Output](#expected-output)

## Repository structure
This repository is organized into several branches, each focusing on different aspects of the project. Below is a brief 
overview of the structure and purpose of each branch: 
### Main Branch
- Contains the core implementation of the parallel matrix transposition program. 
- Includes the primary README and documentation. 
### LoopUnroll Branch
- Focuses on implementing and testing the implicit parallelization by enabling only automatic loop unrolling.  
### Vectorization Branch
- Focuses on implementing and testing the implicit parallelization by enabling only automatic vectorization.
### Vectorization_loopUnroll Branch
- Focuses on implementing and testing the implicit parallelization by enabling automatic loop unrolling and automatic vectorization.
### O1 Branch
- Focuses on implementing and testing implicit parallelization by enabling all optimizations from the O1 compilation flag.
### O2 Branch
- Focuses on implementing and testing implicit parallelization by enabling all optimizations from the O2 compilation flag.

## Build instructions
To build the final executable use the following command:
```shell 
make run
```

To delete the folders and files created with the previous command, use:
```shell
make clean
```

The final executable will be located at `` bin/run/main.out ``.

## Execution instructions
The executable generated using the steps in the [Build instructions](#build-intructions)
supports the passing of parameters via command line arguments. The possible arguments are:
- `-s <size>`: Argument used to set the size of the matrix.
- `-m <size>`: Argument used to set the exponent for the minimum size of the matrix (2^exponent).
- `-M <size>`: Argument used to set the exponent for the maximum size of the matrix (2^exponent).
- `-h`: Show help information.

The program supports two ways of setting the matrix size:

1) Use the `-s` argument to set a single size for the matrix.

2) Use `-m` and `-M` to iterate through different matrix sizes as powers of 2.

Note: The two ways of passing the matrix size cannot be used simultaneously.

### Examples

Set a single matrix size:
```shell
./bin/run/main.out -s 12 # sizes: 2^12
```

Set a range of matrix sizes:
```shell
./bin/run/main.out -m 4 -M 12 # sizes: 2^4 -> 2^12
```

### Expected Output

When you run the program with the above commands, you should see whether the matrix is symmetric, the time it took to 
compute both the matrix's symmetry and its transposition for each algorithm (serial, implicit parallelism, and OpenMP), 
and for OpenMP, also the efficiency and speedup.