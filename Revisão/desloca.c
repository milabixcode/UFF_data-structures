#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista
{
    int info;
    struct lista *prox;
} TLSE;

// 1 2 3
// se n impar o ultimo vira o primeiro 3 1 2
// se nao o primeiro vira o ultimo 2 3 1
TLSE *desloca(TLSE *l, int n)
{
    if (!l || l->prox == NULL)
    {
        return l;
    }

    if (n % 2 == 0)
    {
        TLSE *primeiro = l;
        while (l->prox != NULL)
        {
            l = l->prox;
        }
        l->prox = primeiro;
        l = primeiro->prox;
        primeiro->prox = NULL;
        return l;
    }
    else
    {
        TLSE *primeiro = l;
        while (l->prox->prox != NULL)
        {
            l = l->prox;
        }
        TLSE *ultimo = l->prox;
        ultimo->prox = primeiro;
        l->prox = NULL;
        return ultimo;
    }
}

TLSE *insere_fim(TLSE *li, int i)
{
    TLSE *novo = (TLSE *)malloc(sizeof(TLSE));
    novo->info = i;
    novo->prox = NULL;
    TLSE *p = li;
    TLSE *q = li;
    while (p != NULL)
    {
        /* encontra o ultimo elemento */
        q = p;
        p = p->prox;
    }
    if (q != NULL) /* se a lista original não estiver vazia */
        q->prox = novo;
    else
        li = novo;
    return li;
}

void imprime_lista(TLSE *li)
{
    TLSE *p;
    for (p = li; p != NULL; p = p->prox)
        printf("%d ", p->info);
}

int main(void)
{
    /* A função main lê os dados de entrada, cria a lista e chama a função altera
     * depois imprime a lista resultante
     * Ela NÃO DEVE SER MODIFICADA
     * */
    TLSE *lista = NULL;
    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int valor;

    /* lê valores para criar a lista
     * valores devem ser informados separados por traço
     * exemplo: 1-3-5-2-7-9-21-6 */
    printf("Insira os valores da lista separados por - \n");
    scanf("%s", l);
    // quebra a string de entrada
    ptr = strtok(l, delimitador);
    while (ptr != NULL)
    {
        valor = atoi(ptr);
        lista = insere_fim(lista, valor);
        ptr = strtok(NULL, delimitador);
    }
    TLSE *lista_desloc = desloca(lista, 2);
    imprime_lista(lista_desloc);
}