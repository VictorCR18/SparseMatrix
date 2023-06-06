#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <stdexcept>

#include "Node.h"

class SparseMatrix {
private:
    Node* m_head;

public:
    SparseMatrix();
    SparseMatrix(int m, int n);
    ~SparseMatrix();
    void insert(int m, int n, double value);
    double get(int m, int n);
    void print();
};

SparseMatrix::SparseMatrix() {
    m_head = new Node;
    m_head->linha = -1;
    m_head->coluna = -1;
    m_head->direita = m_head;
    m_head->abaixo = m_head;
}

SparseMatrix::SparseMatrix(int m, int n) {
    if (m <= 0 || n <= 0) {
        throw std::invalid_argument("Tamanho inválido da matriz. Os valores devem ser inteiros positivos.");
    }

    m_head = new Node;
    m_head->linha = m;
    m_head->coluna = n;
    m_head->direita = m_head;
    m_head->abaixo = m_head;
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

void SparseMatrix::insert(int m, int n, double value) {
    if (m < 0 || n < 0 || m >= m_head->linha || n >= m_head->coluna) {
        throw std::out_of_range("Posição inválida na matriz.");
    }

    Node* novo = new Node;
    novo->linha = m;
    novo->coluna = n;
    novo->valor = value;

    Node* anteriorLinha = m_head;
    while (anteriorLinha->abaixo != m_head && anteriorLinha->abaixo->linha <= m) {
        anteriorLinha = anteriorLinha->abaixo;
    }

    if (anteriorLinha->abaixo != m_head && anteriorLinha->abaixo->linha == m && anteriorLinha->abaixo->coluna <= n) {
        Node* anteriorColuna = anteriorLinha->abaixo;
        while (anteriorColuna->direita != anteriorLinha && anteriorColuna->direita->coluna < n) {
            anteriorColuna = anteriorColuna->direita;
        }

        if (anteriorColuna->direita != anteriorLinha && anteriorColuna->direita->coluna == n) {
            anteriorColuna->direita->valor = value;
            delete novo;
            return;
        }

        novo->direita = anteriorColuna->direita;
        anteriorColuna->direita = novo;
    } else {
        novo->direita = anteriorLinha->direita;
        anteriorLinha->abaixo = novo;
    }

    Node* anteriorColuna = m_head;
    while (anteriorColuna->direita != m_head && anteriorColuna->direita->coluna <= n) {
        anteriorColuna = anteriorColuna->direita;
    }

    novo->abaixo = anteriorColuna->direita;
    anteriorColuna->direita = novo;
}


double SparseMatrix::get(int m, int n) {
    if (m < 0 || n < 0 || m >= m_head->linha || n >= m_head->coluna) {
        throw std::out_of_range("Posição inválida na matriz.");
    }

    Node* auxLinha = m_head->abaixo;

    // Percorrer a lista encadeada na linha correta
    while (auxLinha != m_head && auxLinha->linha < m) {
        auxLinha = auxLinha->abaixo;
    }

    if (auxLinha != m_head && auxLinha->linha == m) {
        Node* auxColuna = auxLinha->direita;

        // Percorrer a lista encadeada na coluna correta
        while (auxColuna != auxLinha && auxColuna->coluna < n) {
            auxColuna = auxColuna->direita;
        }

        if (auxColuna != auxLinha && auxColuna->coluna == n) {
            return auxColuna->valor;
        }
    }

    return 0.0;
}


void SparseMatrix::print() {
    int m = m_head->linha;
    int n = m_head->coluna;

    for (int i = 0; i < m; i++) {
        Node* linhaAtual = m_head->abaixo;

        for (int j = 0; j < n; j++) {
            if (linhaAtual != m_head && linhaAtual->linha == i) {
                if (linhaAtual->coluna == j) {
                    std::cout << linhaAtual->valor << " ";
                    linhaAtual = linhaAtual->direita;
                } else {
                    std::cout << "0 ";
                }
            } else {
                std::cout << "0 ";
            }
        }

        std::cout << std::endl;
    }
}


#endif
