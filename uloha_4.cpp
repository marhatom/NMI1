#include <iostream>
#include <cmath>
#include <petscvec.h>
#include <petscmat.h>
#include <petscksp.h>

int main(int argc,char **args) {
  int n = 100000;
  int m = sqrt(n);   
  
  /* Inicializace */
  CHKERRQ( PetscInitialize( &argc , &args , (char *)0 , 0 ) );

  /* Vytvoreni vektoru a nastaveni jeho celkove velikosti na 10 a hodnot na 0 */
  Vec y;
  VecCreateMPI(PETSC_COMM_WORLD, PETSC_DECIDE, n, &y);
  VecSet(y, 2.0);

  // Vytvoreni matice o velkosti 10x10
  Mat A;
  MatCreate(PETSC_COMM_WORLD, &A);
  MatSetSizes(A, PETSC_DECIDE, PETSC_DECIDE, n, n);
  MatSetFromOptions(A);
  MatSetUp(A);

  // Nastaveni prvku na 1, -2, 1
  PetscInt istart, iend;
  MatGetOwnershipRange(A, &istart, &iend);
		for (int i=istart; i<iend; i++) {
			MatSetValue(A, i, i, 4, INSERT_VALUES);
			if(i < n-1) MatSetValue(A, i+1, i, -1, INSERT_VALUES);
			if(i > 0) MatSetValue(A, i-1, i, -1, INSERT_VALUES);
			if(i < n-m) MatSetValue(A, i+m, i, -1, INSERT_VALUES);
			if(i > m-1) MatSetValue(A, i-m, i, -1, INSERT_VALUES);
  }
  MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
  MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);


  // Reseni soustavy Ax = y
  Vec x;
  VecDuplicate(y, &x);

  KSP solver;
  KSPCreate(PETSC_COMM_WORLD, &solver);
  KSPSetOperators(solver, A, A);


  KSPSetType(solver, KSPCG);
  PC prec;
  KSPGetPC(solver,&prec);
  PCSetType(prec,PCJACOBI);

  KSPSetFromOptions(solver);
  KSPSetUp(solver);

  KSPSolve(solver, y, x);

  VecView(x, PETSC_VIEWER_STDOUT_WORLD);

  KSPDestroy(&solver);
  MatDestroy(&A);
  VecDestroy(&x);
  VecDestroy(&y);

  CHKERRQ( PetscFinalize() );

  return 0;
}
