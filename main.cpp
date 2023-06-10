#include <iostream>
#include <fstream>
#include "SparseMatrix.h" // Supondo que você tenha implementado a classe SparseMatrix

using namespace std;

SparseMatrix* sum(SparseMatrix* A, SparseMatrix* B) {
    // Verifica se as matrizes têm o mesmo tamanho
    if (A->getMaxM() != B->getMaxM() || A->getMaxN() != B->getMaxN()) {
        throw std::invalid_argument("As matrizes devem ter o mesmo tamanho para serem somadas.");
    }

    int m = A->getMaxM();
    int n = A->getMaxN();

    // Cria uma nova matriz C com o mesmo tamanho de A e B
    SparseMatrix* C = new SparseMatrix(m, n);

    // Percorre todas as posições da matriz
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // Obtém os valores de A e B nas posições (i, j)
            double valueA = A->get(i, j);
            double valueB = B->get(i, j);

            // Calcula a soma dos valores e insere na matriz C
            double sum = valueA + valueB;
            C->insert(i, j, sum);
        }
    }

    return C; // Retorna a matriz C resultante da soma de A e B
}

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
