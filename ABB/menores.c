// Função que retorna num vetor todos os elementos menores que N

#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TABB;

int qtd_menores(TABB *a, int N)
{
    if (!a)
    {
        return 0;
    }

    int contador = 0;
    if (a->info < N)
    {
        contador += 1;
    }

    contador += qtd_menores(a->esq, N);
    contador += qtd_menores(a->dir, N);

    return contador;
}

void grava_vetor(TABB *a, int N, int* vetor, int* contador){
    if(!a){
        return;
    }

    if (a->info < N) {
        vetor[*contador] = a->info;
        *contador += 1;
    }

    grava_vetor(a->esq, N, vetor, contador);
    grava_vetor(a->dir, N, vetor, contador);
}

int *mN(TABB *a, int N)
{
    if (!a)
    {
        return NULL;
    }

    int n = qtd_menores(a, N);
    int *vetor = (int *)malloc(n * sizeof(int));
    int contador = 0;

    grava_vetor(a, N, vetor, &contador);

    return vetor;
}