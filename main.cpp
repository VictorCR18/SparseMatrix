// Antonio Victor Cavalcante Rodrigues - 535739
// Nauan Aires de Castro e Silva - 536825

#include <iostream>
#include <fstream>
#include "SparseMatrix.h"

using namespace std;

SparseMatrix *readSparseMatrix(const std::string &nomeArquivo){
    std::ifstream arquivo(nomeArquivo);
    if(!arquivo.is_open()){
        throw std::runtime_error("Nao foi possivel abrir o arquivo: " + nomeArquivo);
    }

    int m, n;
    arquivo >> m >> n; // Lê as dimensões da matriz

    SparseMatrix *matriz = new SparseMatrix(m, n);

    while(true){
        double value;
        arquivo >> m >> n >> value;
        if(arquivo.eof()) break;
        matriz->insert(m, n, value);
    }

    arquivo.close();

    return matriz;
}

SparseMatrix *sum(SparseMatrix *A, SparseMatrix *B){
    // Verifica se as matrizes têm o mesmo tamanho
    if(A->getMaxM() != B->getMaxM() || A->getMaxN() != B->getMaxN()){
        throw std::invalid_argument("As matrizes devem ter o mesmo tamanho para serem somadas.");
    }

    int m = A->getMaxM();
    int n = A->getMaxN();

    // Cria uma nova matriz C com o mesmo tamanho de A e B
    SparseMatrix *C = new SparseMatrix(m, n);
    // Percorre todas as posições da matriz
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
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

SparseMatrix *multiply(SparseMatrix *A, SparseMatrix *B) {
    if(A->getMaxN() != B->getMaxM()){
        throw std::runtime_error("As matrizes nao podem ser multiplicadas. O numero de colunas de A deve ser igual ao numero de linhas de B.");
    }
    
    int m = A->getMaxM();
    int n = B->getMaxN();
    int p = B->getMaxM();
    
    SparseMatrix *C = new SparseMatrix(m, p);  // C terá dimensões m x p
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < p; j++){
            int sum = 0;
            for(int k = 0; k < n; k++){
                sum += A->get(i, k) * B->get(k, j);  // Multiplica os elementos correspondentes e soma
            }
            if(sum != 0){
                C->insert(i, j, sum);  // Insere o elemento não nulo na matriz resultante C
            }
        }
    }
    
    return C;
}

int main(){
    while(true){
        cout << endl << "1 - Adicionar Matriz: " << endl;
        cout << "2 - Somar Matrizes: " << endl;
        cout << "3 - Multiplicar Matrizes: " << endl;
        cout << "4 - Abrir arquivo:  " << endl;
        cout << "5 - Sair: " << endl << endl;
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

            int c {0};
            while(c == 0){
                cout << "Insira a posicao e valor na matriz: ";
                cin >> m >> n >> value;
                matriz->insert(m, n, value);
                cout << endl;
                matriz->print();
                cout << endl;
                cout << "Finalizar?" << endl;
                cout << "1 - Sim" << endl << "0 - Nao" << endl;
                cin >> c;
                cout << endl;
            }

            cout << "Matriz adicionada com sucesso!" << endl << endl;
            cout << "Salvar em um arquivo?" << endl;
            cout << "1 - Sim" << endl << "0 - Nao" << endl << endl;
            int key;
            cin >> key;
            if(key == 1){
                cout << "Digite o nome do arquivo para salvar a matriz: ";
                string filename;
                cin >> filename;

                ofstream file(filename);
                if(!file.is_open()){
                    throw std::runtime_error("Nao foi possivel abrir o arquivo: " + filename);
                }

                file << matriz->getMaxM() << " " << matriz->getMaxN() << std::endl;

                for(int i = 0; i < matriz->getMaxM(); i++) {
                    for(int j = 0; j < matriz->getMaxN(); j++) {
                        double value = matriz->get(i, j);
                        if(value != 0.0){
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
                cout << endl << "Digite o nome do arquivo da primeira matriz: ";
                string filenameA;
                cin >> filenameA;

                SparseMatrix *A = readSparseMatrix(filenameA);
                
                cout << "Digite o nome do arquivo da segunda matriz: ";
                string filenameB;
                cin >> filenameB;

                SparseMatrix *B = readSparseMatrix(filenameB);

                SparseMatrix *C = sum(A, B);
                cout << "Matriz multiplicada com sucesso!" << endl;
                cout << endl;
                C->print();
                cout << endl;
                cout << "Salvar em um arquivo?" << endl;
                cout << "1 - Sim" << endl << "0 - Nao" << endl;
                int key;
                cin >> key;
                if(key == 1){
                    cout << "Digite o nome do arquivo para salvar a matriz: ";
                    string filename;
                    cin >> filename;

                    ofstream file(filename);
                    if(!file.is_open()){
                        throw std::runtime_error("Nao foi possível abrir o arquivo: " + filename);
                    }

                    file << C->getMaxM() << " " << C->getMaxN() << std::endl;

                    for (int i = 0; i < C->getMaxM(); i++) {
                        for (int j = 0; j < C->getMaxN(); j++) {
                            double value = C->get(i, j);
                            if(value != 0.0){
                                file << i << " " << j << " " << value << std::endl;
                            }
                        }
                    }

                    file.close();

                    cout << "Matriz salva com sucesso!" << endl;
                    cout << endl;
                }


                // Liberar memória
                delete A;
                delete B;
                delete C;

                break;
            }
            case 3: {
                cout << endl << "Digite o nome do arquivo da primeira matriz: ";
                string filenameA;
                cin >> filenameA;

                SparseMatrix *A = readSparseMatrix(filenameA);
                
                cout << "Digite o nome do arquivo da segunda matriz: ";
                string filenameB;
                cin >> filenameB;

                SparseMatrix *B = readSparseMatrix(filenameB);

                SparseMatrix *C = multiply(A, B);
                cout << "Matriz multiplicada com sucesso!" << endl;
                cout << endl;
                C->print();
                cout << endl;
                cout << "Salvar em um arquivo?" << endl;
                cout << "1 - Sim" << endl << "0 - Nao" << endl;
                int key;
                cin >> key;
                if(key == 1){
                    cout << "Digite o nome do arquivo para salvar a matriz: ";
                    string filename;
                    cin >> filename;

                    ofstream file(filename);
                    if(!file.is_open()){
                        throw std::runtime_error("Nao foi possivel abrir o arquivo: " + filename);
                    }

                    file << C->getMaxM() << " " << C->getMaxN() << std::endl;

                    for(int i = 0; i < C->getMaxM(); i++){
                        for(int j = 0; j < C->getMaxN(); j++){
                            double value = C->get(i, j);
                            if(value != 0){
                                file << i << " " << j << " " << value << std::endl;
                            }
                        }
                    }

                    file.close();

                    cout << "Matriz salva com sucesso!" << endl;
                    cout << endl;
                }

                // Liberar memória
                delete A;
                delete B;
                delete C;

                break;
            }
            case 4: {
                cout << endl << "Digite o nome do arquivo da matriz: ";
                string filenameA;
                cin >> filenameA;
                cout << endl;
                SparseMatrix *A = readSparseMatrix(filenameA);
                A->print();

                break;
            }
            case 5:{
                cout << "Saindo..." << endl;
                return 0;
            }
            default: {
                cout << "Opçao invalida!" << endl;
                break;
            }
        }
    }

    return 0;
}
