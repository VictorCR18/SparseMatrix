#include <iostream>
#include <fstream>
#include "SparseMatrix.h"

using namespace std;

SparseMatrix* readSparseMatrix(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo: " + nomeArquivo);
    }

    int m, n;
    arquivo >> m >> n; // Lê as dimensões da matriz

    SparseMatrix* matriz = new SparseMatrix(m, n);

    int linha, coluna;
    double valor;
    while (arquivo >> linha >> coluna >> valor) {
        matriz->insert(linha, coluna, valor); // Insere os elementos na matriz
    }

    arquivo.close();

    return matriz;
}


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
            C->print();
            cout << valueA << " " << valueB << " "  << sum << endl;
            cout << endl;
        }
    }

    return C; // Retorna a matriz C resultante da soma de A e B
}

int main(){
    while (true){
        cout << "1 - Adicionar Matriz: " << endl;
        cout << "2 - Somar Matrizes: " << endl;
        cout << "3 - Sair: " << endl;
        cout << "Opcao: ";
        int op;
        cin >> op;
        switch(op){
            case 1: {
            cout << endl << "Criacao da matriz..." << endl;
            int m, n, value;
            cout << "Insira o numero de linhas e colunas: ";
            cin >> m >> n;

            SparseMatrix* matriz = new SparseMatrix(m, n);

            cout << endl;
            matriz->print();
            cout << endl;

            int c {1};
            while (c == 1) {
                cout << "Insira a posicao e valor na matriz: ";
                cin >> m >> n >> value;
                matriz->insert(m, n, value);
                cout << endl;
                matriz->print();
                cout << endl;
                cout << "Finalizar?" << endl;
                cout << "1 - Nao" << endl << "0 - Sim" << endl;
                cin >> c;
                cout << endl;
            }

            cout << "Matriz adicionada com sucesso!" << endl << endl;
            cout << "Salvar em um arquivo?" << endl;
            cout << "1 - Sim" << endl << "0 - Nao" << endl;
            int key;
            cin >> key;
            if (key == 1) {
                cout << "Digite o nome do arquivo para salvar a matriz: ";
                string filename;
                cin >> filename;

                ofstream file(filename);
                if (!file.is_open()) {
                    throw std::runtime_error("Não foi possível abrir o arquivo: " + filename);
                }

                file << matriz->getMaxM() << " " << matriz->getMaxN() << std::endl;

                for (int i = 0; i < matriz->getMaxM(); i++) {
                    for (int j = 0; j < matriz->getMaxN(); j++) {
                        double value = matriz->get(i, j);
                        if (value != 0.0) {
                            file << i << " " << j << " " << value << std::endl;
                        }
                    }
                }

                file.close();

                cout << "Matriz salva com sucesso!" << endl;
            }
            break;
        }


            case 2: {
                cout << "Digite o nome do arquivo da primeira matriz: ";
                string filenameA;
                cin >> filenameA;

                // Abre o arquivo da primeira matriz para leitura
                ifstream fileA(filenameA);
                if (!fileA.is_open()) {
                    cout << "Erro ao abrir o arquivo da primeira matriz." << endl;
                    break;
                }

                int mA, nA;
                fileA >> mA >> nA;

                // Cria uma matriz A
                SparseMatrix* A = new SparseMatrix(mA, nA);

                 while (true) {
                    double value;
                    fileA >> mA >> nA >> value;
                    if( fileA.eof() ) break;
                    A->insert(mA, nA, value);
                }

                fileA.close();

                cout << "Digite o nome do arquivo da segunda matriz: ";
                string filenameB;
                cin >> filenameB;

                // Abre o arquivo da segunda matriz para leitura
                ifstream fileB(filenameB);
                if (!fileB.is_open()) {
                    cout << "Erro ao abrir o arquivo da segunda matriz." << endl;
                    break;
                }

                int mB, nB;
                fileB >> mB >> nB;

                // Cria uma matriz B
                SparseMatrix* B = new SparseMatrix(mB, nB);

                while (true) {
                    double value;
                    fileB >> mB >> nB >> value;
                    if( fileB.eof() ) break;
                    B->insert(mB, nB, value);
                }

                fileB.close();

                SparseMatrix* C = sum(A, B);
                cout << "Matriz somada com sucesso!" << endl;
                cout << endl;
                C->print();
                cout << endl;
                break;
            }
            case 3: {
                cout << "Saindo..." << endl;
                return 0;
            }
            default: {
                cout << "Opção inválida!" << endl;
                break;
            }
        }
    }

    return 0;
}
