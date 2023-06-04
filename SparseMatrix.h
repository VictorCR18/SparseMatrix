#ifndef SPARCEMATRIX_H
#define SPARCEMATRIX_H
#include "Node.h"

class SparseMatrix{
private:
    Node *m_head;
public:
    SparseMatrix(int n, int m);
    ~SparseMatrix();
    void insert(int i, int j, double value);
    double get(int i, int j);
    void print();
};

SparseMatrix::SparseMatrix(int n, int m){
}

SparseMatrix::~SparseMatrix(){
}

void SparseMatrix::insert(int i, int j, double value){
    
}

double SparseMatrix::get(int i, int j){
    return 0;
}



#endif SPARCEMATRIX_H