#include <iostream>
#include <fstream>
#include "SparseMatrix.h" // Supondo que você tenha implementado a classe SparseMatrix

using namespace std;

int main(){
    cout << "Criacao da matriz" << endl;
    int m, n, value;
    cin >> m >> n;
    SparseMatrix matrix(m, n); // Criando uma matriz esparsa com m linhas e n colunas
    cout << endl;
    matrix.print(); // Imprimindo a matriz esparsa
    cout << endl;

    while(true) {
        cout << "Digite o numero da linha e coluna e o valor" << endl;
        cin >> m >> n >> value; // Entrando com a linha, coluna e valor para o elemento da matriz
        matrix.insert(m, n, value); // Inserindo o valor na matriz esparsa na posição especificada
        cout << endl;
        matrix.print(); // Imprimindo a matriz esparsa
        cout << endl;
    }

    return 0;
}
