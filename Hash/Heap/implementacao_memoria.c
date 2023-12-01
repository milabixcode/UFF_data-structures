#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// IMPLEMENTAÇÃO EM MEMÓRIA
// Lembrar que os índices assumem que o primeiro elemento estána posição 1 do vetor,
//  e não na posição 0

int pai(int i)
{
    return i / 2;
}
int esq(int i)
{
    return (i * 2);
}
int dir(int i)
{
    return (i * 2 + 1);
}

// Alteração de Prioridade
// Aumentar prioridade
void subir(int *heap, int i)
{
    // pego o pai de i
    int j = pai(i);
    // j tem que ser igual ou maior que 1
    if (j >= 1)
    {
        // se filho é maior que o pai
        if (heap[i] > heap[j])
        {
            // faz a subida
            int temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;
            subir(heap, j);
        }
    }
}

// Diminuir prioridade
// recebe como parametros: i(indice do elemento que precisa descer)
// n:tamanho da heap
void descer(int *heap, int i, int n)
{
    // Descubro quem é o maior filho de i
    int e = esq(i);
    int d = dir(i);
    int maior = i;
    // e<= n : checo se não é uma folha
    if (e <= n && heap[e] > heap[i])
    {
        maior = e;
    }
    if (d <= n && heap[d] > heap[maior])
    {
        maior = d;
    }
    if (maior != i)
    {
        // faz descida trocando com o maior filho
        int temp = heap[i];
        heap[i] = heap[maior];
        heap[maior] = temp;
        descer(heap, maior, n);
    }
}

// Inserção: insiro no final da lista (n+1)
// chamo função de subida pra arrumar a prioridade
int insere(int *heap, int novo, int n)
{
    // aumenta o tamanho do vetor
    heap = (int *)realloc(heap, sizeof(int) * (n + 2));
    n = n + 1;
    heap[n] = novo;
    subir(heap, n);
    // retorna o novo valor de n
    return n;
}

// Remoção: sempre do mais prioritário: primeiro elemento da tabela
// Preenche o espaço vazio deixado por ele com o ultimo elemento da tabela
// Execução do algoritmo de descida para corrigir prioridade dessde elemento
int exclui(int *heap, int n)
{
    heap[1] = heap[n];
    n = n - 1;
    // diminui o tamanho do vetor
    heap = (int *)realloc(heap, sizeof(int) * (n + 1));

    descer(heap, 1, n);
    // retorna o novo valor de n
    return n;
}

// Construção de lista de prioridades
// Considero uma heap vazia e ir inserindo os elementos de um a um
// ou considero que a lista é uma heap e corrijo as prioridades
// assumo que as prioridades das folhas já estão corretas
// começo acertando a prioridade de 1/2 e vou diminuindo 1
void constroi_heap_maximo(int *heap, int n)
{
    int i;
    int j = n / 2;
    for (i = j; i >= 1; i--)
    {
        descer(heap, i, n);
    }
}

// Ordenação de dados usando Heap - HEAP SORT
// maior elemento é trocado com o ultimo do vetordição de 
// considerar vetor com tamanho n-1 e descer a raiz
// repetir esses passos n-1 vezes
void heap_sort(int *heap, int n)
{
    int i;
    int j = n;
    constroi_heap_maximo(heap, n);
    for (i = n; i > 1; i--)
    {
        // troca raiz com o último elemento (posição j)
        int temp = heap[i];
        heap[i] = heap[1];
        heap[i] = temp;
        // diminui o tamanho do vetor a ser considerado na heap
        j--;
        // desce com a raiz nessa nova heap de tamanho j-1;
        descer(heap, 1, j);
    }
}

int main(void)
{
    // vetor de inteiros para simplificar
    // na prática seria um vetor de struct com dados
    int *heap;
    int n;

    printf("Digite o tamanho do vetor de elementos: ");
    scanf("%d", &n);
    if (n <= 0)
    {
        return 0;
    }
    // vetor começara em 1, por isso alocação de tamanho n+1
    heap = (int *)malloc(sizeof(int) * (n + 1));
}
