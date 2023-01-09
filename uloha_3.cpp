#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include "suitesparse/umfpack.h"

using namespace std;

struct SparseMatrix {
  int n, m;               // Rozmery matice
  int nnz;                // Pocet nenulovych clenu
  int* cptr;
  int* cidx;
  double* val; 

  ~SparseMatrix() {
    delete[] cptr;
    delete[] cidx;
    delete[] val;
  }
};

void Write2Sparse(const char *filename, int n);
void loadMatrixMM(const char* filename, SparseMatrix& A);

int main() {
    //Write2Sparse("matice.txt", 1000);
    SparseMatrix A;
    loadMatrixMM("matice.txt", A);

    double *b = new double[A.n];    // Prava strana
    double *x = new double[A.n];    // Reseni

    // Vypocet prave strany (reseni je vektor x = [1, 1, 1, ... 1]
    for (int i=0; i<A.n; i++)  
        b[i] = 2;

    // Reseni soustavy pomoci UMFPACKU
    void *Symbolic, *Numeric;
    double Control[UMFPACK_CONTROL];
    double Info[UMFPACK_INFO];

    umfpack_di_defaults(Control);

    Control[UMFPACK_PRL] = 5;   // Nastaveni urovne vypisu
    umfpack_di_report_control(Control);

    // Analyza
    umfpack_di_symbolic(A.n, A.m, A.cptr, A.cidx, A.val, &Symbolic, 
                Control, Info);

    // LU rozklad
    umfpack_di_numeric(A.cptr, A.cidx, A.val, Symbolic, &Numeric, 
                Control, Info);
    if (Info[UMFPACK_STATUS]!=UMFPACK_OK) {
    cerr << "Chyba pri numericke faktorizaci.\n";
    return 1;
    };

    umfpack_di_free_symbolic(&Symbolic);

    // Reseni LU x = b
    umfpack_di_solve(UMFPACK_A, A.cptr, A.cidx, A.val, x, b, Numeric, 
            Control, Info);

    umfpack_di_free_numeric(&Numeric);

    umfpack_di_report_info(Control, Info);

    //for (int i=0; i<A.n; i++) 
    //    x[i];

    delete[] b;
    delete[] x;

    return 0;
}

void Write2Sparse(const char *filename, int n) {
    int num = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                num++;  
            else if ((i == j + 1) || (i == j - 1))
                num++;
            else if ((j == i+int(sqrt(n))) || (j == i-int(sqrt(n))))
                num++;
        }
    }

    ofstream vystupniProud(filename);
    vystupniProud << n << " " << n << " " << num << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                vystupniProud << i+1 << "\t" << j+1 << "\t" << 4 << "\n";  
            else if ((i == j + 1) || (i == j - 1))
                vystupniProud << i+1 << "\t" << j+1 << "\t" << -1 << "\n";
            else if ((j == i+int(sqrt(n))) || (j == i-int(sqrt(n))))
                vystupniProud << i+1 << "\t" << j+1 << "\t" << -1 << "\n";
            
        }
    }


    vystupniProud.close();
}

void loadMatrixMM(const char* filename, SparseMatrix& A) {
    string line;
    ifstream file(filename);
    if (!file.good()) {cerr << "Chyba\n"; exit(1);};

    do {                    // Preskocime hlavicku
    getline(file, line);
    } while (line[0]=='%');

    // Nacti rozmery matice
    stringstream(line) >> A.n >> A.m >> A.nnz;

    // Nacti matici ve formatu i, j, A(i,j) s upravou indexovani od 0
    int *ii = new int[A.nnz];
    int *jj = new int[A.nnz];
    double *AA = new double[A.nnz];
    for (int l = 0; l<A.nnz; l++) {
    file >> ii[l] >> jj[l] >> AA[l];
    ii[l]--;
    jj[l]--;
    };

    // Preved matici na CSC format pomoci funkci UMFPACKu
    A.cptr = new int[A.m+1];
    A.cidx = new int[A.nnz];
    A.val  = new double[A.nnz];

    umfpack_di_triplet_to_col(A.n, A.m, A.nnz, ii, jj, AA, 
                A.cptr, A.cidx, A.val, NULL);
    delete[] ii;
    delete[] jj;
    delete[] AA;
}