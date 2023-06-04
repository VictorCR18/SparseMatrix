#include <iostream>
#include <fstream>
#include "SparseMatrix.h"

int main(){
    // SparseMatrix* readSparseMatrix(std::string nome do arquivo);
    // SparseMatrix* sum(SparseMatrix* A, SparseMatrix* B);
    // SparseMatrix *multiply(SparseMatrix *A, SparseMatrix *B);

    SparseMatrix matrix(4, 4);

    matrix.insert(0, 0, 50.0);
    matrix.insert(0, 1, 30.0);
    matrix.insert(1, 0, 10.0);
    matrix.insert(1, 2, -20.0);
    matrix.insert(3, 3, -5.0);

    matrix.print();

    return 0;
}