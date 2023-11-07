#include <stdio.h>
#include <stdlib.h>

typedef struct a
{
    int info;
    int cor;
    struct a *esq, *dir;
} TAB;

TAB *inicializa(void)
{
    return NULL;
}

TAB *cria(int info, int cor, TAB *esq, TAB *dir)
{
    TAB *novo = (TAB *)malloc(sizeof(TAB));

    novo->info = info;
    novo->cor = cor;
    novo->esq = esq;
    novo->dir = dir;

    return novo;
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

void imprime_cor(TAB *arv)
{
    if (arv)
    {
        imprime_cor(arv->esq);
        printf("%d ", arv->cor);
        imprime_cor(arv->dir);
    }
}
void colore_recurs(TAB *arv)
{
    int cor = !arv->cor;

    if (arv->esq) {
        arv->esq->cor = cor;
        colore_recurs(arv->esq);
    }
    if (arv->dir) {
        arv->dir->cor = cor;
        colore_recurs(arv->dir);
    }
}

void colore(TAB *arv)
{
    if (!arv)
    {
        return;
    }

    int cor;
    printf("Digite 1 para começar com preto e 0 para começar com vermelho:");
    scanf("%d", &cor);
    arv->cor = cor;
    colore_recurs(arv);
}

int main(void)
{
    TAB *arv = cria(100, NULL,
                    cria(50, NULL,
                         cria(20, NULL,
                              cria(10, NULL, NULL, NULL),
                              cria(25,
                                   NULL,
                                   cria(30, NULL, NULL, NULL), NULL)),
                         cria(40, NULL, cria(45, NULL, NULL, NULL), NULL)),
                    NULL);
    colore(arv);
    imprime_simetrico(arv);
    printf("\n");
    imprime_cor(arv);
    printf("\n");
}