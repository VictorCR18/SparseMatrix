#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <stdexcept>

#include "Node.h"

class SparseMatrix {
    private:
        Node *m_head;
        int maxm, maxn;

    public:
        SparseMatrix(int m, int n);
        ~SparseMatrix();
        void insert(int m, int n, double value);
        double get(int m, int n);
        void print();
        int getMaxM() const {
            return maxm;
        };
        int getMaxN() const {
            return maxn;
        };
};

SparseMatrix::SparseMatrix(int m, int n){
    if (m <= 0 || n <= 0) {
        throw std::invalid_argument("Tamanho invalido da matriz. Os valores devem ser inteiros positivos.");
    }

    this->maxn = n;
    this->maxm = m;
    this->m_head = new Node(nullptr, nullptr, -1, -1, 0);

    Node *aux = this->m_head;

    for(int i = 0; i < m; i++){
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

    this->m_head->linha = 0;
    this->m_head->coluna = 0;
}

SparseMatrix::~SparseMatrix(){
    Node *auxLinha = m_head->abaixo;

    while (auxLinha != m_head) {
        Node *auxColuna = auxLinha->direita;
        while (auxColuna != auxLinha) {
            Node *temp = auxColuna;
            auxColuna = auxColuna->direita;
            delete temp;
        }
        Node *temp = auxLinha;
        auxLinha = auxLinha->abaixo;
        delete temp;
    }

    delete m_head;
}
void SparseMatrix::insert(int m, int n, double value){
    // Verifica se as coordenadas estão dentro dos limites válidos da matriz
    if (m < 0 || n < 0 || m >= this->maxm || n >= this->maxn){
        throw std::out_of_range("Posição inválida na matriz.");
    }

    // Encontra o nó da linha apropriada para inserção
    Node *linhaH = this->m_head->abaixo;

    while (linhaH != m_head && linhaH->linha < m){
        linhaH = linhaH->abaixo;
    }

    // Encontra o nó da coluna apropriada para inserção
    Node *colunaH = m_head->direita;

    while (colunaH != m_head && colunaH->coluna < n){
        colunaH = colunaH->direita;
    }

    // Encontra o nó vizinho à direita na mesma linha
    Node *noVizinhoC = linhaH;

    while (noVizinhoC->direita != linhaH && noVizinhoC->direita->coluna < n){
        noVizinhoC = noVizinhoC->direita;
    }

    // Encontra o nó vizinho abaixo na mesma coluna
    Node *noVizinhoL = colunaH;

    while (noVizinhoL->abaixo != colunaH && noVizinhoL->abaixo->linha < m){
        noVizinhoL = noVizinhoL->abaixo;
    }

    // Se o elemento já existe na posição, atualiza seu valor
    if (noVizinhoL->direita->linha == m && noVizinhoC->abaixo->coluna == n){
        noVizinhoL->valor = value;
        return;
    }

    // Cria um novo nó e o insere na posição apropriada
    Node *novo = new Node(noVizinhoC->direita, noVizinhoL->abaixo, m, n, value);
    noVizinhoC->direita = novo; 
    noVizinhoL->abaixo = novo;
}

double SparseMatrix::get(int m, int n){
    // Verifica se as coordenadas estão dentro dos limites válidos da matriz
    if (m < 0 || n < 0 || m >= this->maxm || n >= this->maxn){
        throw std::out_of_range("Posicao invalida na matriz.");
    }

    // Encontra o nó da linha correta na lista encadeada
    Node *linhaH = m_head->abaixo;

    while (linhaH != m_head && linhaH->linha < m){
        linhaH = linhaH->abaixo;
    }

    // Verifica se a linha correta foi encontrada
    if (linhaH != m_head && linhaH->linha == m){
        Node *colunaH = linhaH->direita;
        // Percorre os nós na linha até encontrar a coluna desejada
        while (colunaH != linhaH && colunaH->coluna != n){
            colunaH = colunaH->direita;
        }

        // Verifica se a coluna correta foi encontrada
        if (colunaH != linhaH && colunaH->coluna == n){
            return colunaH->valor; // Retorna o valor do nó
        }
    }

    return 0; // Retorna 0 se não foi encontrado nenhum valor na posição especificada
}

void SparseMatrix::print(){
    int m = this->maxm; // Armazena o número de linhas da matriz
    int n = this->maxn; // Armazena o número de colunas da matriz

    for (int i = 0; i < m; i++){ // Percorre as linhas da matriz
        for (int j = 0; j < n; j++){ // Percorre as colunas da matriz
            std::cout << get(i, j) << " "; // Obtém o valor da posição (i, j) e imprime na tela
        }
        std::cout << '\n'; // Quebra de linha após imprimir uma linha completa da matriz
    }
}

#endif
