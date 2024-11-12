# parallel-matrix-transposition

## Build intructions
To build the final executable use:
```shell 
make run
```

The final executable will be located at `` bin/run/a.out ``.

## Debug instructions

If needed, the executable can be built with the debugging flag ``-g``. In order to do so use:
```shell
make debug
```
The executable will be located at `` bin/debug/a.out ``

## Execution instructions

The executable generated using the steps in the [Build instructions](#build-intructions) and [Debug instructions](#debug-instructions)
supports the passing of parameters via command line arguments. The possible arguments are:
- -s \<size\>: Mandatory argument used to set the size of the matrix
- -h: Show help information