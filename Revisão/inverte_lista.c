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
    int contador = 1;
    if (l == NULL)
    {
        contador = 0;
    }
    else
    {
        while (l->prox != NULL)
        {
            contador += 1;
            l = l->prox;
        }
    }
    return contador;
}

// int tam_lista_alternativo(TLSE *l)
// {
//     int contador = 0;
//     while(l) {
//         contador += 1;
//         l = l->prox;
//     }
//     return contador;
// }

void swap(TLSE *a, TLSE *b)
{
    int tmp = a->info;
    a->info = b->info;
    b->info = tmp;
}

TLSE *acha_no(TLSE *l, int posicao)
{
    for (int i = 0; i < posicao; i++)
    {
        l = l->prox;
    }
    return l;
}

//Escreva uma função em C que, dada uma lista l qualquer, inverta os elementos de l
void inverte(TLSE *l)
{
    int tam = tam_lista(l);

    for (int i = 0; i < tam / 2; i++)
    {
        TLSE *primeiro = acha_no(l, i);
        TLSE *ultimo = acha_no(l, tam - 1 - i);
        swap(primeiro, ultimo);
    }
}

TLSE *insere_inicio(TLSE *l, int valor)
{
    if (!l)
    {
        TLSE *l = (TLSE *)malloc(sizeof(TLSE));
        l->info = valor;
        l->prox = NULL;
        return l;
    }
    else
    {
        TLSE *novo = (TLSE *)malloc(sizeof(TLSE));
        novo->info = valor;
        novo->prox = l;
        return novo;
    }
}

//inverte os elementos de l em uma outra lista de saída. Portanto, a lista de entrada não pode ser alterada.
TLSE *inverte_sem_alterar(TLSE *l)
{
    int tam = tam_lista(l);
    TLSE *pilha = NULL;
    for (int i = 0; i < tam; i++)
    {
        pilha = insere_inicio(pilha, l->info);
        l = l->prox;
    }
    return pilha;
}

void inverte_hard(TLSE *l)
{
    if (!l || !l->prox)
    {
        return;
    }

    TLSE *anterior = NULL;
    TLSE *atual = l;
    TLSE *proximo = NULL;
    TLSE *segundo = l->prox;
    // int tam = tam_lista(l);
    //  faço o ponteiro ir ate o ultimo elemento da lista
    //  faço o ultimo elemento da lista antiga ser o primeiro da lista nova
    //  o anterior da lista antiga vira o proximo da lista nova

    while ((atual->prox != NULL))
    {
        // inverte
        proximo = atual->prox;
        atual->prox = anterior;
        // anda pra frente
        anterior = atual;
        atual = proximo;
    }
    atual->prox = anterior;

    TLSE temp = *atual;
    *atual = *l;
    *l = temp;
    segundo->prox = atual;
}

void imprime_lista(TLSE *li)
{
    TLSE *p;
    for (p = li; p != NULL; p = p->prox)
        printf("%d ", p->info);
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
    TLSE *pilha = inverte_sem_alterar(lista);
    imprime_lista(lista);
    printf("\n");
    imprime_lista(pilha);
}