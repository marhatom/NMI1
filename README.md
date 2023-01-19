# Restricted access
![shrekando](https://user-images.githubusercontent.com/91134821/211408165-bce9278c-1119-445e-bca8-001336040a86.png)

## LAPACK
- [Manual](https://netlib.org/lapack/lug/node11.html)
```
$ sudo apt install liblapacke-dev
$ g++ file.cpp -llapacke
$ ./a.out
```

## UMFPack
- [Manual](https://users.encs.concordia.ca/~krzyzak/R%20Code-Communications%20in%20Statistics%20and%20Simulation%202014/Zubeh%F6r/SuiteSparse/UMFPACK/Doc/UserGuide.pdf)
```
$ sudo apt-get install libsuitesparse-dev
$ g++ file.cpp -lumfpack
$ ./a.out
```

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
PETSc.pc := $(PETSC_DIR)/$(PETSC_ARCH)/lib/pkgconfig/PETSc.pc
PACKAGES := $(PETSc.pc)

CXX = mpic++

CXXFLAGS = $(shell pkg-config --cflags $(PACKAGES))
LDFLAGS = $(shell pkg-config --libs-only-L $(PACKAGES)) 
LDFLAGS += -Wl,-rpath,$(shell pkg-config --variable=libdir $(PACKAGES)) 
LDLIBS = $(shell pkg-config --libs-only-l $(PACKAGES))
```
Compile and run:
```
$ make uloha_4
$ ./uloha_4
```
(_alternatively_) 
``` 
$ make uloha_4
$ mpiexec -np 4 ./uloha_4 
```

