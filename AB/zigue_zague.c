// Função para testar se uma árvore é zigue-zague (todos
// os nós internos possuem exatamente uma sub-árvore vazia)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct a
{
    int info;
    struct a *esq, *dir;
} TAB;

TAB *inicializa(void)
{
    return NULL;
}
TAB *criaArvore(char entrada[100], int tamanho)
{
    char novaEntrada[100];
    int i, j;
    TAB *novo;
    novo = NULL;
    if ((tamanho > 0) && (entrada[0] != '*'))
    {
        novo = (TAB *)malloc(sizeof(TAB));
        novo->info = entrada[0];
        tamanho = tamanho / 2;

        // divide a entrada em duas partes e chama a função criaArvore recursivamente
        i = 1; // inicio da subarvore esquerda na string entrada
        j = 0; // cursor da nova string de entrada que conterá apenas a subárvore desejada
        while (i <= tamanho)
        {
            novaEntrada[j] = entrada[i];
            i++;
            j++;
        }
        novaEntrada[i] = '\0';
        novo->esq = criaArvore(novaEntrada, tamanho);

        i = tamanho + 1; // inicio da subarvore direita na string entrada
        j = 0;           // cursor da nova string de entrada que conterá apenas a subárvore desejada
        while (i <= tamanho * 2)
        {
            novaEntrada[j] = entrada[i];
            i++;
            j++;
        }
        novaEntrada[i] = '\0';
        novo->dir = criaArvore(novaEntrada, tamanho);
    }
    return novo;
}

int zz(TAB *a)
{

    if (!a)
    {
        return 1;
    }

    if (a->esq && a->dir)
    {
        return 0;
    }

    if(a->esq || a->dir ) {
       
        return (zz(a->esq) && zz(a->dir));
    }
    return 1;
}