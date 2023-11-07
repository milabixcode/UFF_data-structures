#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNoA
{
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

TNoA *maior(TNoA *a)
{
    if (!a)
    {
        return NULL;
    }

    TNoA *maior_no = a;
    while (maior_no->dir)
    {
        maior_no = maior_no->dir;
    }
    return maior_no;
}

TNoA *menor(TNoA *a)
{
    if (!a)
    {
        return NULL;
    }

    TNoA *menor_no = a;
    while (menor_no->esq)
    {
        menor_no = menor_no->esq;
    }
    return menor_no;
}

TNoA *exclui(TNoA *raiz, int chave)
{
    if (!raiz)
    {
        return raiz;
    }
    // se chave é menor que raiz->chave
    if (chave < raiz->chave)
    {
        raiz->esq = exclui(raiz->esq, chave);
    }
    // se a chave é maior que raiz->chave
    else if (chave > raiz->chave)
    {
        raiz->dir = exclui(raiz->dir, chave);
    }
    // achou a chave
    //  3 cenarios: 1)nao tem filhos 2)tem um filho 3)tem dois filhos
    else
    {
        // não tem filhos
        if (!raiz->esq && !raiz->dir)
        {
            free(raiz);
            return NULL;
        }
        // 1 filho: tem so dir ou so esq
        else if (!raiz->esq || !raiz->dir)
        {
            if (!raiz->dir)
            {
                TNoA *aux = raiz->esq;
                free(raiz);
                raiz = aux;
            }
            else
            {
                TNoA *aux = raiz->dir;
                free(raiz);
                raiz = aux;
            }
        }
        // 2 filhos: tem esq e dir
        else
        {
            TNoA *filho = raiz->esq;
            while (filho->dir)
            {
                filho = filho->dir;
            }
            raiz->chave = filho->chave;
            filho->chave = chave;
            raiz->esq = exclui(raiz->esq, chave);
        }
    }
    return raiz;
}

void imprime(TNoA *nodo, int tab)
{
    for (int i = 0; i < tab; i++)
    {
        printf("-");
    }
    if (nodo != NULL)
    {
        printf("%d\n", nodo->chave);
        imprime(nodo->esq, tab + 2);
        printf("\n");
        imprime(nodo->dir, tab + 2);
    }
    else
        printf("vazio");
}

TNoA *insere(TNoA *no, int chave)
{
    if (no == NULL)
    {
        no = (TNoA *)malloc(sizeof(TNoA));
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
    }
    else if (chave < (no->chave))
        no->esq = insere(no->esq, chave);
    else if (chave > (no->chave))
    {
        no->dir = insere(no->dir, chave);
    }
    else
    {
        printf("Inserção inválida! ");
        exit(1);
    }
    return no;
}

int main(void)
{

    /* A função main lê os dados de entrada, cria a árvore e chama a função solicitada no problema
     * depois imprime o resultado solicitado
     * ELA NÃO DEVE SER MODIFICADA
     * */
    TNoA *raiz;
    raiz = NULL;

    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int valor;

    /* lê valores para criar a arvore
     * valores devem ser informados separados por traço
     * exemplo: 1-3-5-2-7-9-21-6 */
    scanf("%s", l);
    // quebra a string de entrada
    ptr = strtok(l, delimitador);
    while (ptr != NULL)
    {
        valor = atoi(ptr);
        raiz = insere(raiz, valor);
        ptr = strtok(NULL, delimitador);
    }

    // le valor a ser excluido
    scanf("%d", &valor);
    // Chama função
    raiz = exclui(raiz, valor);
    imprime(raiz, 0);
};