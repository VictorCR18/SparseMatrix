#ifndef NODE_H
#define NODE_H

struct Node {
    Node *direita;
    Node *abaixo;
    int linha;
    int coluna;
    double valor;

    Node(Node *dir, Node *ab, int l, int c, double v) {
        this->direita = dir;
        this->abaixo = ab;
        this->linha = l;
        this->coluna = c;
        this->valor = v;
    }
};

#endif