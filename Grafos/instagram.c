#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vizinho
{
    char nome[10];
    struct vizinho *prox;
} TVizinho;

typedef struct grafo
{
    char nome[10];
    int idade;
    TVizinho *prim_vizinho;
    struct grafo *prox;
} TGrafo;

TGrafo *insere_vertice(TGrafo *g, char *nome, int idade)
{
    TGrafo *vertice = (TGrafo *)malloc(sizeof(TGrafo));
    strcpy(vertice->nome, nome);
    vertice->idade = idade;
    vertice->prox = g;
    vertice->prim_vizinho = NULL;
    return vertice;
}

TGrafo *busca_vertice(TGrafo *vertice, char *nome)
{
    while ((vertice != NULL) && (strcmp(vertice->nome, nome) != 0))
    {
        vertice = vertice->prox;
    }
    return vertice;
}

TVizinho *busca_vizinho(TVizinho *vizinho, char *nome)
{
    while ((vizinho != NULL) && (strcmp(vizinho->nome, nome) != 0))
    {
        vizinho = vizinho->prox;
    }
    return vizinho;
}

void insere_aresta(TGrafo *g, char *nome_origem, char *nome_destino)
{
    TGrafo *vertice = busca_vertice(g, nome_origem);
    TVizinho *vizinho = (TVizinho *)malloc(sizeof(TVizinho));
    strcpy(vizinho->nome, nome_destino);
    vizinho->prox = vertice->prim_vizinho;
    vertice->prim_vizinho = vizinho;
}

void imprime(TGrafo *vertice)
{
    while (vertice != NULL)
    {
        printf("Pessoa: %s - %d anos\n", vertice->nome, vertice->idade);
        printf("Segue: ");
        TVizinho *vizinho = vertice->prim_vizinho;
        while (vizinho != NULL)
        {
            printf("%s ", vizinho->nome);
            vizinho = vizinho->prox;
        }
        printf("\n\n");
        vertice = vertice->prox;
    }
}

int igual(char *a, char *b)
{
    return !strcmp(a, b);
}

// numero de arestas
int numero_seguidos(TGrafo *g, char *nome)
{
    while (g != NULL && !igual(g->nome, nome))
    {
        g = g->prox;
    }
    int seguidos = 0;
    if (g != NULL && igual(g->nome, nome))
    {
        TVizinho *temp = g->prim_vizinho;
        while (temp != NULL)
        {
            seguidos += 1;
            temp = temp->prox;
        }
    }
    return seguidos;
}

int numero_seguidos_2(TGrafo *g, char *nome)
{
    for (TGrafo *vertice = g; vertice != NULL; vertice = vertice->prox)
    {
        if (igual(vertice->nome, nome))
        {
            int contador = 0;
            for (TVizinho *vizinho = vertice->prim_vizinho; vizinho != NULL; vizinho = vizinho->prox)
            {
                contador += 1;
            }
            return contador;
        }
    }
    return 0;
}

// vertices que contem aquele vertice
int seguidores(TGrafo *g, char *nome, int imprime)
{
    int contador = 0;
    while (g != NULL)
    {
        TVizinho *temp = g->prim_vizinho;
        while (temp != NULL && !igual(temp->nome, nome))
        {
            temp = temp->prox;
        }
        if (temp != NULL)
        {
            contador += 1;

            if (imprime)
            {
                printf("%s ", g->nome);
            }
        }
        g = g->prox;
    }

    if (imprime)
    {
        printf("\n");
    }
    return contador;
}

int seguidores_2(TGrafo *g, char *nome, int imprime)
{
    int contador = 0;
    for (TGrafo *vertice = g; vertice != NULL; vertice = vertice->prox)
    {
        for (TVizinho *vizinho = vertice->prim_vizinho; vizinho != NULL; vizinho = vizinho->prox)
        {
            if (igual(vizinho->nome, nome))
            {
                {
                    contador += 1;
                    break;
                }
            }
        }
    }
    return contador;
}

// tem mais seguidores
TGrafo *mais_popular(TGrafo *g)
{
    int mais_seguidores = 0;
    int numero_seguidores = 0;
    TGrafo *mais_pop = NULL;
    for (TGrafo *vertice = g; vertice != NULL; vertice = vertice->prox)
    {
        numero_seguidores = seguidores(g, vertice->nome, 0);
        if (numero_seguidores > mais_seguidores)
        {
            mais_seguidores = numero_seguidores;
            mais_pop = vertice;
        }
    }
    return mais_pop;
}

int segue_mais_velho(TGrafo *g, int imprime)
{
    int qtd = 0;
    for (TGrafo *vertice = g; vertice != NULL; vertice = vertice->prox)
    {
        int tem_mais_jovem = 0;
        for (TVizinho *vizinho = vertice->prim_vizinho; vizinho != NULL; vizinho = vizinho->prox)
        {
            TGrafo *no_vizinho = NULL;
            for (TGrafo *vertice = g; vertice != NULL; vertice = vertice->prox)
            {
                if (igual(vizinho->nome, vertice->nome))
                {
                    no_vizinho = vertice;
                }
            }

            if (no_vizinho != NULL && no_vizinho->idade <= vertice->idade)
            {
                tem_mais_jovem = 1;
            }
        }
        if (vertice->prim_vizinho != NULL && !tem_mais_jovem)
        {
            qtd += 1;
            if (imprime)
            {
                printf("%s ", vertice->nome);
            }
        }
    }

    if (imprime)
    {

        printf("\n");
    }
    return qtd;
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

int main()
{
    /* A função main lê os dados de entrada, cria o grafo e chama as funções solicitadas no problema
     * depois imprime os resultados solicitados
     * ELA NÃO DEVE SER MODIFICADA
     * */
    int num_vertices, num_arestas;
    char nome[30];
    char origem[30], destino[30];
    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int idade;
    int i;
    TGrafo *g = NULL;

    // le numero de vertices
    scanf("%d", &num_vertices);
    // le e cria os vertices
    for (i = 0; i < num_vertices; i++)
    {
        scanf("%s", l);
        // quebra a string de entrada
        ptr = strtok(l, delimitador);
        strcpy(nome, ptr);
        // printf("%s", nome);
        ptr = strtok(NULL, delimitador);
        idade = atoi(ptr);
        g = insere_vertice(g, nome, idade);
    }

    // Le numero de arestas e depois le os dados de cada aresta
    // Cria as arestas no grafo
    scanf("%d", &num_arestas);
    for (i = 0; i < num_arestas; i++)
    {
        scanf("%s", l);
        // quebra a string de entrada
        ptr = strtok(l, delimitador);
        strcpy(origem, ptr);
        // printf("%s", nome);
        ptr = strtok(NULL, delimitador);
        strcpy(destino, ptr);
        insere_aresta(g, origem, destino);
    }

    // Le nome de pessoa
    scanf("%s", nome);

    // Encontra o número de seguidos dessa pessoa
    printf("SEGUIDOS por %s: %d\n", nome, numero_seguidos(g, nome));

    // Encontra os seguidores de uma determinada pessoa
    printf("SEGUIDORES de %s:\n", nome);
    seguidores(g, nome, 1);

    TGrafo *p;

    // Encontra mais popular
    p = mais_popular(g);
    printf("MAIS POPULAR: %s\n", p->nome);

    // Encontra as pessoas que seguem apenas pessoas mais velhas
    printf("SEGUEM APENAS PESSOAS MAIS VELHAS:\n");
    segue_mais_velho(g, 1);

    libera_vertice(g);
}