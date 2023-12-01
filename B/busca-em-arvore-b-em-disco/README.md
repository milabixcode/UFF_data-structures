[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/szPeo_ar)
#### Problema

Implemente a função int busca(int chave, char *nome\_arquivo\_metadados, char *nome\_arquivo\_indice, char *nome\_arquivo\_dados) que recebe como parâmetro a chave a ser buscada e os nomes dos 3 arquivos que armazenam a árvore B+ e retorna o endereço do nó em que a chave está ou que deveria estar. A função deve imprimir os nós avaliados até que o nó onde a chave está ou deveria estar tenha sido encontrado (use as funções de impressão fornecidas). 

A árvore armazena registros de clientes, cuja estrutura e funções auxiliares estão no arquivo cliente.c. Uma árvore exemplo é fornecida e está disponível nos arquivos metadados.dat (que contém os metadados), indice.dat (que contém os nós internos da árvore) e clientes.dat (que contém os nós folha da árvore).

#### Entrada

- chave a ser buscada
- nome do arquivo de metadados (esse arquivo contém a ordem d da árvore B+, o ponteiro para a raiz da árvore, e um flag que indica se a raiz é folha ou um nó interno. Sua estrutura e funcões auxiliares estão no arquivo metadados.c)
- nome do arquivo de índice (esse arquivo contém os nós internos da árvore B+, e sua estrutura e funções auxiliares estão no arquivo no\_interno.c)
- nome do arquivo de dados (esse arquivo contém os nós folhas da árvore B+, e sua estrutura e funções auxiliares estão no arquivo no\_folha.c)

#### Saída 

- endereço do nó onde a chave está ou deveria estar 
- a função deve imprimir todos os nós avaliados durante a busca, usando para isso as funções imprime\_no\_interno e imprime\_no\_folha

#### Exemplo 

Usando os arquivos fornecidos para teste nesse exercício (metadados.dat, indice.dat e clientes.dat), e assumindo que se deseja buscar a chave **20**, seu programa deve gerar a seguinte saída. 

```
NO INTERNO: (m = 1, pt pai = -1, aponta folha = 0)
	[48]  37 [96]  -1 [-1]  -1 [-1]  -1  [-1] 

NO INTERNO: (m = 2, pt pai = 0, aponta folha = 1)
	[0]  15 [428]  25 [856]  -1 [-1]  -1  [-1] 

NO FOLHA: (m = 2, pt pai = 48, pt prox = 856)
	15, Jose
	20, Mariana
		
RESULTADO DA BUSCA: 428
```

Uma busca pela chave **18** resultaria na mesma resposta acima, apesar dessa chave não existir no nó folha exibido na resposta. Se ela existisse, estaria nesse nó. 

#### Função imprime\_no\_interno

A função imprime um nó interno que foi lido do arquivo de índice (use a função le\_no\_interno para isso). Na primeira linha são impressos os metadados do nó. Na segunda linha, são impressos os ponteiros (entre colchetes) e as chaves do nó, conforme exemplo abaixo. Ponteiros para NULL são representados por -1. Chaves não existentes (ou seja, espaços vazios no nó) são representadas por -1. O exemplo abaixo mostra um nó raiz (pois pt pai = -1), que não aponta para uma folha (pois aponta folha = 0) que tem a chave 37. O ponteiro da esquerda dessa chave é o 48 e o da direita é o 96. Os valores dos ponteiros são absolutos, ou seja, não é necessário calcular nada para usar esse valor. Para acessar o nó apontado pelo ponteiro 48, basta fazer fseek (no arquivo de índice, pois esse nó aponta para um outro nó interno da árvore) usando 48 como valor do descolamento, e SEEK\_SET.


```
NO INTERNO: (m = 1, pt pai = -1, aponta folha = 0)
	[48]  37 [96]  -1 [-1]  -1 [-1]  -1  [-1] 
```

#### Função imprime\_no\_folha

A função imprime um nó folha que foi lido do arquivo de dados (use a função le\_no\_folha para isso). Na primeira linha são impressos os metadados do nó. Na segunda linha, são impressos os registros armazenados no nó (que nesse exemplo, são registros de clientes com código e nome), conforme exemplo abaixo. No exemplo abaixo, existem dois registros armazenados nessa folha (com chaves 15 e 20), o nó pai tem endereço 48 e o próximo nó folha tem endereço 856. 

```
NO FOLHA: (m = 2, pt pai = 48, pt prox = 856)
	15, Jose
	20, Mariana
```

#### Função imprime\_arquivos

Use essa função caso você queira ver o conteúdo dos três arquivos de entrada. Não esqueça de comentar o uso dela antes de entregar a versão final do seu código, caso contrário isso afetará a saída gerada pelo seu programa, e os casos de teste irão falhar. 

#### Arquivos a modificar

Modifique apenas o arquivo **arvore\_b\_mais.c**, com sua função de busca implementada. 

#### Dicas Importantes: 

- Os arquivos de entrada devem ser colocados dentro da pasta cmake\_build\_debug do projeto caso você esteja usando o CLion
- A entrada e a saída já são tratadas no arquivo fornecido para ler e imprimir os dados no formato esperado pela questão. Vocês devem APENAS implementar a função solicitada no problema
- Não use arquivos .h (coloque todas as definições de tipo no arquivo .c)
- Não altere/delete o arquivo "cases_data.bin"
