# parallel-matrix-transposition

## Build intructions
To build the final executable use:
```shell 
make run
```

The final executable will be located at `` bin/run/a.out ``.

## Debug instructions

If needed, the executable can be built with the debugging flag. In order to do so use:
```shell
make debug
```
The executable will be located at `` bin/debug/a.out ``

## Execution instructions

The executable generated using the steps in the [Build instructions](#build-intructions) and [Debug instructions](#debug-instructions)
support the passage of parameters via command line arguments. The possible arguments are:
- -s \<size\>: Mandatory parameter used to set the size of the matrix
- -h: Show help information to the user