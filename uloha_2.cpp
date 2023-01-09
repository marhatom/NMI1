#include <iostream>
#include <cmath>
#include <lapacke.h>

using namespace std;

class Matrix {
public:

  Matrix(size_t rows, size_t cols):
    rows_(rows),
    cols_(cols)
  { data_ = new double[rows*cols]; }

  ~Matrix() { delete[] data_; }

  size_t rows() const { return rows_; }
  size_t cols() const { return cols_; }
  size_t lda() const { return cols_; }

  double* data() { return data_; }

  double* operator[](int row) { return data_ + row*lda(); }

private:
  size_t rows_;
  size_t cols_;
  double* data_;
};

int main() {
    int n = 1000;

    double* y = new double[n];
    double alpha = 1.0;
    double beta = 1.0;

    Matrix A(n, n);

    for (size_t i=0; i<n; i++) {
        for (size_t j=0; j<n; j++) 
        if ((j == i+1) || (j == i-1))
            A[i][j] = -1;
        else if ((j == i+int(sqrt(n))) || (j == i-int(sqrt(n))))
            A[i][j] = -1;
        else
            A[i][j] = 0;
        
        A[i][i] = 4;
        y[i] = 2.0;
    }

    int* ipiv = new int[n];

    // vypis matice A
    /*
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
    */

    cout << endl;

    for (size_t i=0; i<A.rows(); i++)
      cout << "y[" << i << "] = " << y[i] << endl;

    cout << endl;
    
    int info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, A.rows(), 1, A.data(), A.lda(), ipiv, y, 1);

    cout << "info = " << info << endl;

    for (size_t i=0; i<A.rows(); i++)
      cout << "y[" << i << "] = " << y[i] << endl;

    cout << endl;

    delete[] ipiv;
    delete[] y;

    return 0;
}