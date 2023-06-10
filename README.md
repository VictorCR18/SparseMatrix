# SparseMatrix.h

O código apresentado define o construtor da classe `SparseMatrix`, que cria uma matriz esparsa com tamanho `m` por `n`. A matriz esparsa é uma estrutura de dados otimizada para armazenar matrizes que possuem a maioria dos elementos com valor zero.

Aqui está uma explicação linha por linha do código:

1. Verifica se os valores `m` e `n` são positivos. Caso contrário, lança uma exceção com uma mensagem de erro.

2. Atribui o valor de `n` para a variável `maxn` da classe.

3. Atribui o valor de `m` para a variável `maxm` da classe.

4. Cria um novo nó (`m_head`) que representa a cabeça da matriz.

5. Cria um ponteiro `aux` e o aponta para o nó `m_head`.

6. Inicia um loop para criar os nós das linhas da matriz.

7. Cria um novo nó abaixo do nó atual (`aux`) com valores específicos: ponteiros `acima` e `abaixo` são inicializados com `nullptr`, `linha` recebe o valor de `i`, `coluna` recebe -1 (valor inválido para coluna) e `valor` recebe 2 (valor temporário para identificar um nó de linha).

8. Atualiza o ponteiro `aux` para apontar para o novo nó criado.

9. Atribui o ponteiro `aux` ao ponteiro `abaixo` do novo nó criado.

10. Define o ponteiro `direita` do novo nó criado para apontar para ele mesmo, indicando que é o último nó na linha.

11. Define o ponteiro `abaixo` do novo nó criado para apontar para a cabeça da matriz (`m_head`), fechando o loop circular da linha.

12. Atualiza o ponteiro `aux` para apontar novamente para a cabeça da matriz (`m_head`).

13. Inicia um loop para criar os nós das colunas da matriz.

14. Cria um novo nó à direita do nó atual (`aux`) com valores específicos: ponteiros `esquerda` e `direita` são inicializados com `nullptr`, `linha` recebe -1 (valor inválido para linha) e `coluna` recebe o valor de `i`.

15. Atualiza o ponteiro `aux` para apontar para o novo nó criado.

16. Atribui o ponteiro `aux` ao ponteiro `direita` do novo nó criado.

17. Define o ponteiro `abaixo` do novo nó criado para apontar para ele mesmo, indicando que é o último nó na coluna.

18. Define o ponteiro `direita` do novo nó criado para apontar para a cabeça da matriz (`m_head`), fechando o loop circular da coluna.

19. Define o valor da variável `linha` do nó da cabeça da matriz (`m_head`) como 0, indicando que é a linha atual.

20. Define o valor da variável `coluna` do nó da cabeça da matriz (`m_head`) como 0, indicando que é a coluna atual.

Em resumo, o construtor cria uma matriz esparsa representada por uma lista circular duplamente encadeada, onde cada
nó representa um elemento não nulo da matriz. A cabeça da matriz (`m_head`) é uma estrutura especial que armazena informações sobre o tamanho da matriz. Os nós adicionais são criados para representar as linhas e colunas da matriz, e os ponteiros são configurados de forma a formar loops circulares que facilitam as operações na matriz.

--------------------------------------------------------------------------------------------------------------------

O código apresentado define o destrutor da classe `SparseMatrix`, responsável por liberar a memória alocada para os nós da matriz esparsa. Aqui está uma explicação linha por linha do código:

1. Cria um ponteiro `auxLinha` e o inicializa com o nó abaixo da cabeça da matriz (`m_head->abaixo`).

2. Inicia um loop enquanto o ponteiro `auxLinha` não apontar para a cabeça da matriz (`m_head`).

3. Cria um ponteiro `auxColuna` e o inicializa com o nó à direita do nó atual (`auxLinha->direita`).

4. Inicia um loop enquanto o ponteiro `auxColuna` não apontar para o nó atual (`auxLinha`).

5. Cria um ponteiro `temp` e o inicializa com o nó atual (`auxColuna`).

6. Atualiza o ponteiro `auxColuna` para apontar para o próximo nó à direita (`auxColuna->direita`).

7. Libera a memória alocada para o nó atual (`temp`) utilizando o operador `delete`.

8. Cria um ponteiro `temp` e o inicializa com o nó atual (`auxLinha`).

9. Atualiza o ponteiro `auxLinha` para apontar para o próximo nó abaixo (`auxLinha->abaixo`).

10. Libera a memória alocada para o nó atual (`temp`) utilizando o operador `delete`.

11. Libera a memória alocada para a cabeça da matriz (`m_head`) utilizando o operador `delete`.

Em resumo, o destrutor percorre a matriz esparsa, começando pelas linhas, liberando a memória alocada para cada nó individualmente, e finalmente liberando a memória alocada para a cabeça da matriz. Isso garante que todos os nós e a estrutura da matriz sejam corretamente desalocados da memória quando o objeto `SparseMatrix` é destruído.

--------------------------------------------------------------------------------------------------------------------

Este método `insert` é responsável por inserir um valor em uma determinada posição da matriz esparsa. Ele percorre a matriz procurando a posição correta para inserir o novo valor, levando em consideração as ordens das linhas e colunas.

Os passos do método são os seguintes:

1. Verifica se as coordenadas (m, n) estão dentro dos limites válidos da matriz. Caso contrário, lança uma exceção de `std::out_of_range` com uma mensagem de erro.

2. Encontra o nó apropriado da linha para inserção. Percorre os nós das linhas até encontrar a linha desejada ou atingir a cabeça da matriz.

3. Encontra o nó apropriado da coluna para inserção. Percorre os nós das colunas até encontrar a coluna desejada ou atingir a cabeça da matriz.

4. Encontra o nó vizinho à direita na mesma linha. Percorre os nós à direita até encontrar o nó vizinho ou atingir o nó de início da linha.

5. Exibe as coordenadas do nó vizinho à direita para fins de depuração.

6. Encontra o nó vizinho abaixo na mesma coluna. Percorre os nós abaixo até encontrar o nó vizinho ou atingir o nó de início da coluna.

7. Exibe as coordenadas do nó vizinho abaixo para fins de depuração.

8. Verifica se o elemento já existe na posição especificada. Se existir, atualiza seu valor e retorna.

9. Cria um novo nó com os ponteiros apropriados e o valor especificado.

10. Atualiza os ponteiros do nó vizinho à direita e abaixo para apontarem para o novo nó.

Em resumo, o método `insert` encontra a posição correta na matriz esparsa e insere o novo valor nessa posição. Caso o elemento já exista na posição, ele atualiza o valor existente.

--------------------------------------------------------------------------------------------------------------------

O método `get` é responsável por obter o valor armazenado em uma determinada posição da matriz esparsa. Ele percorre a matriz para encontrar o nó correspondente à linha e coluna especificadas e retorna o valor armazenado nesse nó.

Os passos do método são os seguintes:

1. Verifica se as coordenadas (m, n) estão dentro dos limites válidos da matriz. Caso contrário, lança uma exceção de `std::out_of_range` com uma mensagem de erro.

2. Encontra o nó da linha correta na lista encadeada. Percorre os nós das linhas até encontrar a linha desejada ou atingir a cabeça da matriz.

3. Verifica se a linha correta foi encontrada.

4. Se a linha correta foi encontrada, encontra o nó da coluna correta na linha. Percorre os nós das colunas até encontrar a coluna desejada ou atingir o nó de início da linha.

5. Verifica se a coluna correta foi encontrada.

6. Se a coluna correta foi encontrada, retorna o valor armazenado no nó encontrado.

7. Caso contrário, retorna 0 para indicar que nenhum valor foi encontrado na posição especificada.

Em resumo, o método `get` localiza o nó correspondente à posição desejada na matriz esparsa e retorna o valor armazenado nesse nó.

--------------------------------------------------------------------------------------------------------------------

O método `print` é responsável por imprimir a matriz esparsa na saída padrão. Ele percorre todas as posições da matriz, linha por linha, e imprime o valor de cada posição usando o método `get`.

Os passos do método são os seguintes:

1. Armazena o número de linhas e colunas da matriz nas variáveis `m` e `n`, respectivamente.

2. Inicia um loop para percorrer as linhas da matriz, com a variável `i` iniciando em 0 e indo até `m-1`.

3. Dentro do loop das linhas, inicia um loop para percorrer as colunas da matriz, com a variável `j` iniciando em 0 e indo até `n-1`.

4. Chama o método `get(i, j)` para obter o valor armazenado na posição (i, j) da matriz e imprime esse valor na tela.

5. Após o loop das colunas, imprime um caractere de quebra de linha (`'\n'`) para separar as linhas da matriz.

Em resumo, o método `print` percorre todas as posições da matriz esparsa e imprime os valores correspondentes na saída padrão, formando uma representação visual da matriz.


# main.cpp

A função `SparseMatrix* readSparseMatrix(const std::string& nomeArquivo)` lê uma matriz esparça de um arquivo e retorna um ponteiro para um objeto `SparseMatrix`.

1. Abre o arquivo especificado pelo parâmetro `nomeArquivo` usando `std::ifstream`.

2. Verifica se o arquivo foi aberto com sucesso. Se não, lança uma exceção `std::runtime_error` com uma mensagem de erro.

3. Declara as variáveis `m` e `n` para armazenar as dimensões da matriz.

4. Lê as dimensões da matriz do arquivo usando `arquivo >> m >> n`.

5. Cria um novo objeto `SparseMatrix` com as dimensões lidas.

6. Entra em um loop infinito.

7. Lê os valores de `m`, `n` e `value` do arquivo usando `arquivo >> m >> n >> value`.

8. Verifica se chegou ao final do arquivo (`arquivo.eof()`). Se sim, sai do loop.

9. Insere o valor `value` na posição `(m, n)` da matriz usando o método `matriz->insert(m, n, value)`.

10. Fecha o arquivo.

11. Retorna o ponteiro para o objeto `SparseMatrix` criado.

No geral, a função lê as dimensões da matriz e os valores de células da matriz do arquivo, cria um objeto `SparseMatrix` correspondente e insere os valores lidos na matriz. Em seguida, retorna o ponteiro para essa matriz.

--------------------------------------------------------------------------------------------------------------------

A função `SparseMatrix* sum(SparseMatrix* A, SparseMatrix* B)` realiza a soma de duas matrizes esparsas `A` e `B`. 

1. Verifica se as matrizes têm o mesmo tamanho comparando as dimensões máximas (`getMaxM()` e `getMaxN()`). Se as dimensões forem diferentes, lança uma exceção `std::invalid_argument` com uma mensagem de erro.

2. Obtém as dimensões máximas da matriz `A`.

3. Cria uma nova matriz `C` com as mesmas dimensões de `A` e `B`.

4. Percorre todas as posições da matriz usando dois loops `for` aninhados.

5. Para cada posição `(i, j)` na matriz:
   - Obtém os valores de `A` e `B` nas posições correspondentes usando os métodos `get(i, j)`.
   - Calcula a soma dos valores `valueA` e `valueB`.
   - Insere o valor da soma na posição `(i, j)` da matriz `C` usando o método `insert(i, j, sum)`.

6. Retorna o ponteiro para a matriz `C`, que contém o resultado da soma de `A` e `B`.

Note que essa função assume que as matrizes têm o mesmo tamanho e realiza a soma dos valores correspondentes em cada posição. Caso as matrizes não tenham o mesmo tamanho, uma exceção é lançada.

--------------------------------------------------------------------------------------------------------------------

A função `SparseMatrix* multiply(SparseMatrix* A, SparseMatrix* B)` realiza a multiplicação de duas matrizes esparsas `A` e `B`.

1. Verifica se o número de colunas de `A` é igual ao número de linhas de `B` (`getMaxN()` de `A` é comparado com `getMaxM()` de `B`). Se forem diferentes, lança uma exceção `std::runtime_error` com uma mensagem de erro.

2. Obtém as dimensões máximas de `A`, `B` e define a dimensão de `C` (`m`, `n` e `p`).

3. Cria uma nova matriz `C` com dimensões `m x p` usando `new SparseMatrix(m, p)`.

4. Inicia dois loops `for` aninhados para percorrer as posições da matriz resultante `C`.

5. Para cada posição `(i, j)` na matriz `C`:
   - Inicia uma variável `sum` para armazenar a soma dos produtos dos elementos correspondentes de `A` e `B`.
   - Inicia um terceiro loop `for` para percorrer as posições correspondentes em `A` e `B` (coluna de `A` e linha de `B`).
   - Multiplica os elementos correspondentes de `A` e `B` usando os métodos `get(i, k)` e `get(k, j)`, respectivamente, e soma o resultado na variável `sum`.
   - Verifica se o valor da soma (`sum`) é diferente de zero. Se for diferente de zero, insere o valor na posição `(i, j)` da matriz `C` usando o método `insert(i, j, sum)`.

6. Retorna o ponteiro para a matriz `C`, que contém o resultado da multiplicação de `A` e `B`.

Esta função assume que as matrizes têm as dimensões corretas para multiplicação (o número de colunas de `A` é igual ao número de linhas de `B`). Caso as dimensões não sejam adequadas, uma exceção é lançada.

--------------------------------------------------------------------------------------------------------------------

1. A função `main()` é o ponto de entrada do programa. Dentro dela, há um loop `while(true)` que permite que o programa seja executado continuamente até que o usuário escolha a opção "4" para sair.

2. O programa exibe um menu com quatro opções:

   a. Opção 1: Adicionar Matriz - Solicita ao usuário que insira o número de linhas e colunas da matriz, cria uma matriz esparsa vazia e permite que o usuário insira os valores em posições específicas da matriz. Após cada inserção, a matriz é exibida na tela. O usuário tem a opção de finalizar a adição de valores ou continuar adicionando mais valores. Em seguida, o usuário pode optar por salvar a matriz em um arquivo.

   b. Opção 2: Somar Matrizes - Solicita ao usuário que forneça os nomes de arquivo de duas matrizes armazenadas anteriormente. Em seguida, carrega as matrizes a partir dos arquivos, realiza a soma das matrizes e exibe o resultado na tela. O usuário tem a opção de salvar a matriz resultante em um arquivo.

   c. Opção 3: Multiplicar Matrizes - Funciona de maneira semelhante à opção 2, mas em vez de realizar a soma, realiza a multiplicação das duas matrizes fornecidas.

   d. Opção 4: Sair - Encerra o programa.

3. Cada opção é implementada como um bloco `case` dentro da estrutura `switch(op)`. Dependendo da opção selecionada, o código correspondente será executado.

4. Dentro dos blocos `case`, várias funções e operações são chamadas para realizar as tarefas solicitadas pelo usuário, como criar matrizes, inserir valores, realizar operações de soma e multiplicação, exibir matrizes e salvar matrizes em arquivos.

5. A memória alocada dinamicamente é liberada usando o operador `delete` para evitar vazamentos de memória.