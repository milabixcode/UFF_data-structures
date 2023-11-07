#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct vizinho
{
    int id_vizinho;
    int peso;
    struct vizinho *prox;
} TVizinho;

typedef struct grafo
{
    int id_vertice;
    int cor;
    TVizinho *prim_vizinho;
    struct grafo *prox;
} TGrafo;

TGrafo *insere_vertice(TGrafo *g, int id)
{
    TGrafo *vertice = (TGrafo *)malloc(sizeof(TGrafo));
    vertice->id_vertice = id;
    vertice->cor = -1;
    vertice->prox = g;
    vertice->prim_vizinho = NULL;
    return vertice;
}

void libera_vizinho(TVizinho *vizinho)
{
    if (vizinho != NULL)
    {
        libera_vizinho(vizinho->prox);
        free(vizinho);
    }
}

void libera_vertice(TGrafo *vertice)
{
    if (vertice != NULL)
    {
        libera_vizinho(vertice->prim_vizinho);
        libera_vertice(vertice->prox);
        free(vertice);
    }
}

TGrafo *busca_vertice(TGrafo *vertice, int id)
{
    while ((vertice != NULL) && (vertice->id_vertice != id))
    {
        vertice = vertice->prox;
    }
    return vertice;
}

TVizinho *busca_vizinho(TVizinho *vizinho, int id)
{
    while ((vizinho != NULL) && (vizinho->id_vizinho != id))
    {
        vizinho = vizinho->prox;
    }
    return vizinho;
}

void insere_aresta(TGrafo *g, int origem, int destino, int peso)
{
    TGrafo *vertice = busca_vertice(g, origem);
    TVizinho *vizinho = (TVizinho *)malloc(sizeof(TVizinho));
    vizinho->id_vizinho = destino;
    vizinho->peso = peso;
    vizinho->prox = vertice->prim_vizinho;
    vertice->prim_vizinho = vizinho;
}

void imprime(TGrafo *vertice)
{
    while (vertice != NULL)
    {
        printf("Vertice: %d\n", vertice->id_vertice);
        printf("Vizinhos: ");
        TVizinho *vizinho = vertice->prim_vizinho;
        while (vizinho != NULL)
        {
            printf("%d ", vizinho->id_vizinho);
            vizinho = vizinho->prox;
        }
        printf("\n\n");
        vertice = vertice->prox;
    }
}
// recebe como parâmetro um grafo valorado e retorna 1 caso ele seja não orientado, e 0 caso contrário
// procuro(a1,a2) procuro (a2,a1) e comparo os pesos. se pesos = entao sao nao orientados
int ehNaoOrientado(TGrafo *g)
{
    TGrafo *vertice = g;
    while (vertice != NULL)
    {
        TVizinho *vizinho = vertice->prim_vizinho;
        while (vizinho != NULL)
        {
            int destino = vizinho->id_vizinho;
            int peso = vizinho->peso;
            TGrafo *verticeDestino = busca_vertice(g, destino);
            TVizinho *vizinhoCorrespondente = busca_vizinho(verticeDestino->prim_vizinho, vertice->id_vertice);
            if (vizinhoCorrespondente == NULL || vizinhoCorrespondente->peso != peso)
            {
                return 0; // Aresta correspondente não encontrada ou pesos diferentes
            }
            vizinho = vizinho->prox;
        }
        vertice = vertice->prox;
    }
    return 1;
}

int main()
{
    /* A função main lê os dados de entrada, cria o grafo e chama a função solicitada no problema
     * depois imprime o resultado
     * ELA NÃO DEVE SER MODIFICADA
     * */
    int num_vertices, num_arestas;
    int id;
    int origem, destino, peso;
    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int i;
    TGrafo *g = NULL;

    // le numero de vertices
    scanf("%d", &num_vertices);
    // le e cria os vertices
    for (i = 0; i < num_vertices; i++)
    {
        scanf("%s", l);
        id = atoi(l);
        g = insere_vertice(g, id);
    }

    // Le numero de arestas e depois le os dados de cada aresta
    // Cria as arestas no grafo
    scanf("%d", &num_arestas);
    for (i = 0; i < num_arestas; i++)
    {
        scanf("%s", l);
        // quebra a string de entrada
        ptr = strtok(l, delimitador);
        origem = atoi(ptr);
        ptr = strtok(NULL, delimitador);
        destino = atoi(ptr);
        ptr = strtok(NULL, delimitador);
        peso = atoi(ptr);
        insere_aresta(g, origem, destino, peso);
    }

    // imprime(g);

    printf("%d", ehNaoOrientado(g));
    libera_vertice(g);
}