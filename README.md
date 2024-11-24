# Parallel Matrix Transposition
This program performs parallel transposition of matrices. Below are the instructions to build and run the program.

## Index 
- [Build Instructions](#build-instructions) 
- [Execution Instructions](#execution-instructions) 
  - [Examples](#examples) 
  - [Expected Output](#expected-output)


## Build intructions
To build the final executable use the following command:
```shell 
make run
```

To delete the folders and files created with the previous command, use:
```shell
make clean
```

The final executable will be located at `` bin/run/a.out ``.

## Execution instructions
The executable generated using the steps in the [Build instructions](#build-intructions)
supports the passing of parameters via command line arguments. The possible arguments are:
- `-s \<size\>`: Argument used to set the size of the matrix.
- `-m \<size\>`: Argument used to set the exponent for the minimum size of the matrix (2^exponent).
- `-M \<size\>`: Argument used to set the exponent for the maximum size of the matrix (2^exponent).
- `-h`: Show help information.

The program supports two ways of setting the matrix size:

1) Use the `-s` argument to set a single size for the matrix.

2) Use `-m` and `-M` to iterate through different matrix sizes as powers of 2.

Note: The two ways of passing the matrix size cannot be used simultaneously.

### Examples

Set a single matrix size:
```shell
./bin/run/a.out -s 12 # sizes: 2^12
```

Set a range of matrix sizes:
```shell
./bin/run/a.out -m 4 -M 12 # sizes: 2^4 -> 2^12
```

### Expected Output

When you run the program with the above commands, you should see whether the matrix is symmetric and the time it took to 
compute both the matrix's symmetry and its transposition for each algorithm (serial, implicit parallelism, and OpenMP).