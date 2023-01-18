# Restricted access
![shrekando](https://user-images.githubusercontent.com/91134821/211408165-bce9278c-1119-445e-bca8-001336040a86.png)

## LAPACK
- [manual](https://netlib.org/lapack/lug/node11.html)

## UMFPack

## The Portable, Extensible Toolkit for Scientific Computation (PETSc)
- [manual](https://www.mcs.anl.gov/petsc/petsc-3.6/docs/manual.pdf)
- Prerequisites - make, python3, C C++ Compiler (e.g. gcc, g++), BLAS/LAPACK, MPI(_Optional_)
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

$ export PETSC_DIR=/cesta/ke/složce/petsc 
$ export PETSC_ARCH=arch-linux-c-debug
```
