#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista
{
    int info;
    struct lista *prox;
} TLSE;

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
/*Defina uma função em C que, dada uma lista l qualquer, retorne, numa lista de saída,
os elementos ímpares e os elementos pares da lista l, na ordem em que os elementos
aparecem em l. Ao final da execução desta função, a lista resultante terá todos os
elementos da lista l (primeiro os ímpares, depois os pares, na ordem em que eles
aparecem em l), e a lista l continuará contendo os seus elementos.*/
TLSE *i_p(TLSE *l)
{
    TLSE *p = l;
    TLSE *lista_pares = NULL;
    TLSE *lista_impares = NULL;
    TLSE *lista_final = NULL;

    while (p)
    {
        if (p->info % 2 == 0)
        {
            lista_pares = insere_fim(lista_pares, p->info);
            p = p->prox;
        }
        else
        {
            lista_impares = insere_fim(lista_impares, p->info);
            p = p->prox;
        }
    }

    // preciso juntar as duas listas agora
    TLSE *q = lista_impares;
    TLSE *temp_par = lista_pares;
    // se q->prox nao for nulo ele vai pro prox
    while (q->prox != NULL)
    {
        q = q->prox;
    }
    q->prox = temp_par;
    return lista_impares;
}

void i_p_parametro(TLSE *l)
{
    
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
    TLSE *lista_final = i_p(lista);
    imprime_lista(lista_final);
}
