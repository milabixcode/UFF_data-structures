#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// implemente a função void altera(TLista* li, int vantigo, int vnovo) que altera o valor do
// campo INFO de uma lista encadeada li, substituindo o valor vantigo pelo valor vnovo
//(ambos passados como parâmetro). Usar o arquivo lista-encadeada.c em anexo, que já
// possui essa função declarada e algumas funções de apoio. Caso vantigo não exista na lista,
// ela deve permanecer inalterada.

typedef struct lista
{
    int info;
    struct lista *prox;
} TLista;

void altera(TLista *li, int vantigo, int vnovo)
{
    // Crio ponteiro para percorrer a lista
    TLista *p = li;

    // Percorre a lista até encontrar o valor antigo ou o final da lista
    while(p != NULL && p->info != vantigo)
    {
        p = p->prox;
    }
    // Verifica se encontrou o valor antigo
    if (p != NULL)
    {
        p->info = vnovo;
    }
}

void imprime_lista(TLista *li)
{
    TLista *p;
    for (p = li; p != NULL; p = p->prox)
        printf("%d ", p->info);
}

TLista *insere_fim(TLista *li, int i)
{
    TLista *novo = (TLista *)malloc(sizeof(TLista));
    novo->info = i;
    novo->prox = NULL;
    TLista *p = li;
    TLista *q = li;
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
    TLista *lista = NULL;
    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int valor;
    int valor_antigo, valor_novo;

    /* lê valores para criar a lista
     * valores devem ser informados separados por traço
     * exemplo: 1-3-5-2-7-9-21-6 */
    printf("Insira os valores da lista separados por -\n");
    scanf("%s", l);
    // quebra a string de entrada
    ptr = strtok(l, delimitador);
    while (ptr != NULL)
    {
        valor = atoi(ptr);
        lista = insere_fim(lista, valor);
        ptr = strtok(NULL, delimitador);
    }

    // Le dados da alteracao a ser realizada
    printf("Insira o valor antigo a ser alterado: ");
    scanf("%d", &valor_antigo);
    printf("Insira o valor novo: ");
    scanf("%d", &valor_novo);
    altera(lista, valor_antigo, valor_novo);
    imprime_lista(lista);
}

