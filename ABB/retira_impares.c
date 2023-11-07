// Função que retira todos os elementos ímpares
#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TABB;

TABB *retira(TABB *a, int x)
{
    if (!a)
    {
        return NULL;
    }

    if (a->info != x)
    {
        a = retira(a->esq, x);
        a = retira(a->dir, x);
    }

    if (a->info == x)
    {
        //NO FOLHA
        if (!a->esq && !a->dir)
        {
            free(a);
            a = NULL;
        }
        //NO COM UM FILHO
        else if (!a->esq || !a->dir)
        {
            TABB *p;
            if (a->esq)
            {
                p = a->esq;
                free(a);
                a = p;
            }
            else
            {
                p = a->dir;
                free(a);
                a = p;
            }
        }
        //NO COM DOIS FILHOS
        else
        {
            TABB *p, *q;
            p = a->esq;
            while (p->dir)
            {
                p = p->dir;
            }
            q = a->esq;
            p->dir = a->dir;
            free(a);
            a = q;
        }
    }

    return a;
}

TABB *retira_impares(TABB *a)
{
    if (!a)
    {
        return NULL;
    }
    TABB *esquerda = retira_impares(a->esq);
    TABB *direita = retira_impares(a->dir);
    
    a->esq = esquerda;
    a->dir - direita;
    
    if (a->info % 2 == 0)
    {
        a = retira(a, a->info);
    }
}