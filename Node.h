#ifndef NODE_H
#define NODE_H

struct Node {
    Node *direita;
    Node *abaixo;
    int linha;
    int coluna;
    double valor;

    Node(Node *direita, Node *abaixo, int lin, int col, double val) {
        this->direita = direita;
        this->abaixo = abaixo;
        this->linha = lin;
        this->coluna = col;
        this->valor = val;
    }
};

#endif