#include <stdio.h>
#include <stdlib.h>

typedef struct a
{
    int info;
    struct a *esq, *dir;
} TAB;

TAB *inicializa(void)
{
    return NULL;
}

TAB *cria(int info, TAB *esq, TAB *dir)
{
    TAB *novo = (TAB *)malloc(sizeof(TAB));

    novo->info = info;
    novo->esq = esq;
    novo->dir = dir;

    return novo;
}

TAB *copia(TAB *a)
{
    if (!a)
    {
        return NULL;
    }

    TAB *arvore_copiada = cria(a->info, copia(a->esq), copia(a->dir));

    return arvore_copiada;
}

TAB *espelho(TAB *a)
{
    if (!a)
    {
        return NULL;
    }

    TAB *arvore_espelhada = cria(a->info, copia(a->dir), copia(a->esq));

    return arvore_espelhada;
}

TAB *maior(TAB *a)
{
    if (!a)
    {
        return NULL;
    }

    TAB *maior_num = a;
    TAB *esquerda = maior(a->esq);
    TAB *direita = maior(a->dir);

    if (esquerda)
    {
        if (esquerda->info > maior_num->info)
        {
            maior_num = esquerda;
        }
    }

    if (direita)
    {
        if (direita->info > maior_num->info)
        {
            maior_num = direita;
        }
    }

    return maior_num;
}

TAB *menor(TAB *a)
{
    if (!a)
    {
        return NULL;
    }

    TAB *menor_num = a;
    TAB *esquerda = menor(a->esq);
    TAB *direita = menor(a->dir);

    if (esquerda)
    {
        if (esquerda->info < menor_num->info)
        {
            menor_num = esquerda;
        }
    }

    if (direita)
    {
        if (direita->info < menor_num->info)
        {
            menor_num = direita;
        }
    }

    return menor_num;
}

// testa se as árvores são iguais
int igual(TAB *a1, TAB *a2)
{
    if (!a1 && !a2)
    {
        return 1;
    }
    if (!a1 || !a2)
    {
        return 0;
    }
    if (a1->info == a2->info)
    {
        if (igual(a1->esq, a2->esq))
        {
            if (igual(a1->dir, a2->dir))
            {
                return 1;
            }
        }
    }
    return 0;
}

TAB *retira(TAB *a, int x)
{
    if (!a)
    {
        return NULL;
    }
    // se ainda não achei o elemento que quero tirar
    if (a->info != x)
    {
        a->esq = retira(a->esq, x);
        a->dir = retira(a->dir, x);
    }
    // se eu achei o elemento que quero tirar
    if (a->info == x)
    {
        // se não tenho nem direita ou esquerda
        if (!a->esq && !a->dir)
        {
            free(a);
            a = NULL;
        }
        // se tenho esquerda ou direita
        else if (!a->esq || !a->dir)
        {
            TAB *aux;
            // se eu tenho esquerda
            if (a->esq)
            {
                aux = a->esq;
                free(a);
                a = aux;
            }
            else
            {
                aux = a->dir;
                free(a);
                a = aux;
            }
        }
        // se eu tenho esquerda e direita
        else
        {
            TAB *p;
            int q;
            p = a->esq;
            while (p->dir)
            {
                p = p->dir;
            }
            q = a->info;
            a->info = p->info;
            p->info = q;
            a = retira(a, p->info);
        }
    }
}

TAB *retira_pares(TAB *a)
{
    if (!a)
    {
        return NULL;
    }
    TAB *esquerda = retira_pares(a->esq);
    TAB *direita = retira_pares(a->dir);

    // os ponteiros arv->esq e arv->dir são atualizados para apontar para as novas árvores
    // obtidas nas chamadas recursivas
    a->esq = esquerda;
    a->dir = direita;

    if (a->info % 2 == 0)
    {
        a = retira(a, a->info);
    }
    return a;
}


void imprime_simetrico(TAB *a)
{
    if (a)
    {
        imprime_simetrico(a->esq);
        printf("%d ", a->info);
        imprime_simetrico(a->dir);
    }
}

int main()
{
    TAB *arvore, *arvore_copiada, *arvore_espelhada;
    // int no_arvore = 5;
    arvore = inicializa();
    arvore = cria(5, NULL, NULL);
    arvore_copiada = copia(arvore);
    imprime_simetrico(arvore_copiada);
    arvore_espelhada = espelho(arvore);
    imprime_simetrico(arvore_espelhada);
    arvore = retira_pares(arvore);
    imprime_simetrico(arvore);
}
