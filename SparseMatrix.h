#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <stdexcept>

#include "Node.h"

class SparseMatrix {
    private:
        Node* m_head;
        int maxm, maxn;

    public:
        SparseMatrix(int m, int n);
        ~SparseMatrix();
        void insert(int m, int n, double value);
        double get(int m, int n);
        void print();
};

SparseMatrix::SparseMatrix(int m, int n) {
    if (m <= 0 || n <= 0) {
        throw std::invalid_argument("Tamanho inválido da matriz. Os valores devem ser inteiros positivos.");
    }

    this->maxn = n;
    this->maxm = m;

    this->m_head = new Node(nullptr, nullptr, -1, -1, 0);

    Node * aux = this->m_head;

    for(int i = 0; i < m; i ++){
        aux->abaixo = new Node(nullptr, nullptr, i, -1, 2);
        aux = aux->abaixo;
        aux->direita = aux;
        aux->abaixo = m_head;
    }

    aux = this->m_head;

    for(int i = 0; i < n; i++){
        aux->direita = new Node(nullptr, nullptr, -1, i, 0);
        aux = aux->direita;
        aux->abaixo = aux;
        aux->direita = m_head;
    }

    this->m_head->linha  = 0;
    this->m_head->coluna = 0;
}

SparseMatrix::~SparseMatrix() {
    Node* auxLinha = m_head->abaixo;

    while (auxLinha != m_head) {
        Node* auxColuna = auxLinha->direita;
        while (auxColuna != auxLinha) {
            Node* temp = auxColuna;
            auxColuna = auxColuna->direita;
            delete temp;
        }
        Node* temp = auxLinha;
        auxLinha = auxLinha->abaixo;
        delete temp;
    }

    delete m_head;
}

// void SparseMatrix::insert(int m, int n, double value) {
//     if (m < 0 || n < 0 || m >= this->maxm || n >= this->maxn) {
//         throw std::out_of_range("Posição inválida na matriz.");
//     }

//     Node * linhaH = this->m_head->abaixo;

//     while (linhaH != m_head && linhaH->linha < m) {
//         linhaH = linhaH->abaixo;
//     }

//     Node * colunaH = linhaH->direita;

//     while (colunaH != m_head && colunaH->coluna < n) {
//         colunaH = colunaH->direita;
//     }

//     Node * noVizinhoC = colunaH;

//     while (noVizinhoC->direita != colunaH && noVizinhoC->direita->coluna <= n) {
//         noVizinhoC = noVizinhoC->direita;
//     }

//     Node * noVizinhoL = colunaH;

//     while (noVizinhoL->abaixo != colunaH && noVizinhoL->abaixo->linha <= m) {
//         noVizinhoL = noVizinhoL->abaixo;
//     }


//     if(noVizinhoL->linha == m && noVizinhoC->coluna == n) {
//         noVizinhoL->valor = value;
//         return;
//     }

//     Node * novo = new Node(noVizinhoL->direita, noVizinhoC->abaixo, m, n, value);
    
//     noVizinhoL->direita = novo;
//     noVizinhoC->abaixo = novo; 
// }


void SparseMatrix::insert(int m, int n, double value) {
    if (m < 0 || n < 0 || m >= this->maxm || n >= this->maxn) {
        throw std::out_of_range("Posição inválida na matriz.");
    }

    Node* linhaH = this->m_head->abaixo;
    while (linhaH != m_head && linhaH->linha < m) {
        linhaH = linhaH->abaixo;
    }

    Node* colunaH = linhaH->direita;
    while (colunaH != linhaH && colunaH->coluna < n) {
        colunaH = colunaH->direita;
    }

    // Node* noVizinhoC = ;
    // while (linhaH != m_head && linhaH->linha < m) {
    //     linhaH = linhaH->abaixo;
    // }

    if (colunaH->linha == m && colunaH->coluna == n) {
        colunaH->valor = value;
        return;
    }

    Node* novo = new Node(linhaH->direita, colunaH->abaixo, m, n, value);

    linhaH->direita = novo;
    colunaH->abaixo  = novo;
}

double SparseMatrix::get(int m, int n) {
    if (m < 0 || n < 0 || m >= this->maxm || n >= this->maxn) {
        throw std::out_of_range("Posição inválida na matriz.");
    }

    Node* linhaH = m_head->abaixo;

    // Percorrer a lista encadeada na linha correta
    while (linhaH != m_head && linhaH->linha < m) {
        linhaH = linhaH->abaixo;
    }
    if (linhaH != m_head && linhaH->linha == m) {
        Node* colunaH = linhaH->direita;

        while (colunaH != linhaH && colunaH->coluna != n) {
            colunaH = colunaH->direita;
        }

        // std::cout << ((colunaH->coluna == n) ? "true" : "false ")<< n << std::endl;
        if (colunaH != linhaH && colunaH->coluna == n) {
            return colunaH->valor;
        }
    }

    return 0;
}



void SparseMatrix::print() {
    int m = this->maxm;
    int n = this->maxn;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << get(i, j) << " ";
        }
        std::cout << '\n';
    }
}



#endif
