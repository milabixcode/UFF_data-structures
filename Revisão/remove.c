#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista
{
    int info;
    struct lista *prox;
} TLSE;

// Remove todas as ocorrências de um elemento numa lista
TLSE *rto(TLSE *l, int elem)
{
    if (!l)
    {
        return NULL;
    }

    TLSE *p = l;
    TLSE *atual = p;
    TLSE *lista = p;
    // 1-2-3-3-4
    // p = 1  atual = 1  lista = 1
    // quando p->prox = 3  p = 2 atual = 3  free(3)  p->prox = 3 p = 2
    // 1-2-3-4
    // quando p->prox = 3  atual = 4  free(3)  p->prox = 4 p = 2
    while (p->prox)
    {
        if (p->prox->info == elem)
        {
            atual = p->prox->prox;
            free(p->prox);
            p->prox = atual;
        }
        else
        {
            p = p->prox;
        }
    }
    if (l->info == 3)
    {
        atual = l->prox;
        free(l);
        return atual;
    }
    return lista;
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
    TLSE *lista_remov = rto(lista, 3);
    imprime_lista(lista_remov);
}
