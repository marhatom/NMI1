# Restricted access
![shrekando](https://user-images.githubusercontent.com/91134821/211408165-bce9278c-1119-445e-bca8-001336040a86.png)

## LAPACK
- [Manual](https://netlib.org/lapack/lug/node11.html)

## UMFPack

## The Portable, Extensible Toolkit for Scientific Computation (PETSc)
- [Manual](https://www.mcs.anl.gov/petsc/petsc-3.6/docs/manual.pdf)
- Prerequisites - make, python3, C C++ Compiler (e.g. gcc, g++), BLAS/LAPACK, MPI
- How to install:

```
$ git clone -b release https://gitlab.com/petsc/petsc.git petsc
```
:warning: directory must not contain any of the following special characters: ~ ! @ # $ % ^ & * ( ) ` ; < > ? , [ ] { } ‘ ” | (including spaces!)
```
$ cd petsc
$ git pull

$ ./configure
$ make all check

$ sudo apt install pkg-config
```

- How to run:
```
$ export PETSC_DIR=/cesta/ke/složce/petsc 
$ export PETSC_ARCH=arch-linux-c-debug
```
Makefile:
```
$ make uloha_4
$ ./uloha_4
```
(_alternatively_) ``` $ mpiexec -np 4 ./uloha_4 ```

