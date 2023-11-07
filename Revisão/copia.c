#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista
{
    int info;
    struct lista *prox;
} TLSE;

int tam_lista(TLSE *l)
{
    int contador = 0;
    if (!l)
    {
        return contador;
    }
    while (l)
    {
        contador += 1;
        l = l->prox;
    }
    return contador;
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

//Implemente uma função que copie uma lista. A lista original deve permanecer inalterada.
TLSE *copia(TLSE *l)
{
    if (!l)
    {
        return NULL;
    }
    TLSE *p = l;
    TLSE *nova = NULL;

    while (p)
    {
        nova = insere_fim(nova, p->info);
        p = p->prox;
    }
    return nova;
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
    TLSE *lista_clonada = copia(lista);
    // imprime_lista(lista);
    imprime_lista(lista_clonada);
}