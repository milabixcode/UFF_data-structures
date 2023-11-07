#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define SEM_COR 1
#define COM_COR 0

typedef struct vizinho
{
    char nome[10];
    struct vizinho *prox;
} TVizinho;

typedef struct grafo
{
    char nome[10];
    int idade;
    int cor;
    TVizinho *prim_vizinho;
    struct grafo *prox;
} TGrafo;

// Descobrir a quantidade de vértices
int nv(TGrafo *g)
{
    if (!g)
    {
        return 0;
    }
    int contador = 0;
    for (TGrafo *vertice = g; vertice != NULL; vertice = vertice->prox)
    {
        contador += 1;
    }
    return contador;
}

// Descobrir número de arestas
int na(TGrafo *g)
{
    if (!g)
    {
        return 0;
    }
    int contador = 0;
    for (TGrafo *vertice = g; vertice != NULL; vertice = vertice->prox)
    {
        for (TVizinho *aresta = vertice->prim_vizinho; aresta != NULL; aresta->prox)
        {
            contador += 1;
        }
    }
    return contador;
}

// verifica se o grafo possui todos os nós com grau igual a k
// grau: grau de um vértice é o número de arestas que nele/dele incidem
int testek(TGrafo *g, int k)
{
    if (!g)
    {
        return 0;
    }
    int contador = 0;
    for (TGrafo *vertice = g; vertice != NULL; vertice = vertice->prox)
    {
        for (TVizinho *aresta_saindo = g->prim_vizinho; aresta_saindo != NULL; aresta_saindo = aresta_saindo->prox)
        {
            contador += 1;
        }

        for (TGrafo *grafo = g; grafo != NULL; grafo = grafo->prox)
        {
            for (TVizinho *aresta_entrando = grafo->prim_vizinho; aresta_entrando != NULL; aresta_entrando = aresta_entrando->prox)
            {
                if (strcmp(vertice->nome, aresta_entrando->nome) == 0)
                {
                    contador += 1;
                }
            }
        }
    }

    if (contador != k)
    {
        return 0;
    }

    return 1;
}

// testa se dois grafos são iguais
int ig(TGrafo *g1, TGrafo *g2)
{
    if (!g1 && !g2)
    {
        return 1;
    }
    if (!g1 || !g2)
    {
        return 0;
    }
    int tam1 = nv(g1);
    int tam2 = nv(g2);
    if (tam1 != tam2)
    {
        return 0;
    }
    for (TGrafo *vertice1 = g1, *vertice2 = g2; vertice1 != NULL && vertice2 != NULL; vertice1 = vertice1->prox, vertice2 = vertice2->prox)
    {
        TVizinho *vizinho1 = vertice1->prim_vizinho;
        TVizinho *vizinho2 = vertice2->prim_vizinho;
        if (strcmp(vertice1->nome, vertice2->nome) != 0)
        {
            return 0;
        }
        for (vizinho1, vizinho2; vizinho1 != NULL && vizinho2 != NULL; vizinho1 = vizinho1->prox, vizinho2 = vizinho2->prox)
        {
            if (strcmp(vizinho1->nome, vizinho2->nome) != 0)
            {
                return 0;
            }
        }
        if (vizinho1 != NULL || vizinho2 != NULL)
        {
            return 0;
        }
    }
    return 1;
}

// testa se nós vizinhos não tem a mesma cor.
// A função retorna um se os vizinhos não tem a mesma cor e zero, caso contrário
int nao_tem_mesma_cor(TGrafo *g)
{
    if (!g)
    {
        return 1;
    }
    for (TGrafo *vertice = g; vertice != NULL; vertice = vertice->prox)
    {
        for (TVizinho *vizinho = vertice->prim_vizinho; vizinho != NULL; vizinho = vizinho->prox)
        {
            for (TGrafo *grafo = g; grafo != NULL; grafo = grafo->prox)
            {
                if (strcmp(grafo->nome, vizinho->nome) == 0)
                {
                    if (grafo->cor == vertice->cor)
                    {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

TGrafo *insere(TGrafo *g, char *nome, int idade, int cor)
{
    TGrafo *vertice = (TGrafo *)malloc(sizeof(TGrafo));
    strcpy(vertice->nome, nome);
    vertice->idade = idade;
    vertice->cor = cor;
    vertice->prox = g;
    vertice->prim_vizinho = NULL;
    return vertice;
}

typedef struct Test
{
    TGrafo *grafo;
    int esperado;
} Test;

TGrafo *busca_vertice(TGrafo *vertice, char *nome)
{
    while ((vertice != NULL) && (strcmp(vertice->nome, nome) != 0))
    {
        vertice = vertice->prox;
    }
    return vertice;
}

TGrafo *cria(char *nome, int idade, int cor)
{
    return insere(NULL, nome, idade, cor);
}

void insere_aresta(TGrafo *g, char *nome_origem, char *nome_destino)
{
    TGrafo *vertice = busca_vertice(g, nome_origem);
    TVizinho *vizinho = (TVizinho *)malloc(sizeof(TVizinho));
    strcpy(vizinho->nome, nome_destino);
    vizinho->prox = vertice->prim_vizinho;
    vertice->prim_vizinho = vizinho;
}

void testes()
{
    {
        char *caso = "grafo_nulo";
        Test t = (Test){.esperado = 1, .grafo = NULL};
        assert(nao_tem_mesma_cor(t.grafo) == t.esperado);
    }

    {
        char *caso = "um_vertice";
        TGrafo *g = cria("bartho", 3, COM_COR);
        Test t = (Test){.esperado = 1, .grafo = g};
        assert(nao_tem_mesma_cor(t.grafo) == t.esperado);
    }

    {
        char *caso = "dois_vertices_mesma_cor";
        TGrafo *g = cria("bartho", 3, COM_COR);
        g = insere(g, "carlinhos", 1, COM_COR);
        insere_aresta(g, "bartho", "carlinhos");

        Test t = (Test){
            .esperado = 0,
            .grafo = g};

        assert(nao_tem_mesma_cor(t.grafo) == t.esperado);
    }

    {
        char *caso = "dois_vertices_mesma_cor";
        TGrafo *g = cria("bartho", 3, COM_COR);
        g = insere(g, "carlinhos", 1, COM_COR);
        insere_aresta(g, "bartho", "carlinhos");

        Test t = (Test){
            .esperado = 0,
            .grafo = g};

        assert(nao_tem_mesma_cor(t.grafo) == t.esperado);
    }

    {
        char *caso = "dois_vertices_cor_diferente";
        TGrafo *g = cria("bartho", 3, COM_COR);
        g = insere(g, "carlinhos", 1, SEM_COR);
        insere_aresta(g, "bartho", "carlinhos");

        Test t = (Test){
            .esperado = 1,
            .grafo = g};

        assert(nao_tem_mesma_cor(t.grafo) == t.esperado);
    }

    {
        char *caso = "cores_alternadas";
        TGrafo *g = cria("bartho", 3, COM_COR);
        g = insere(g, "carlinhos", 1, SEM_COR);
        g = insere(g, "catarina", 1, COM_COR);
        insere_aresta(g, "bartho", "carlinhos");
        insere_aresta(g, "carlinhos", "catarina");
        
        Test t = (Test){
            .esperado = 1,
            .grafo = g};
        
        assert(nao_tem_mesma_cor(t.grafo) == t.esperado);
    }

    {
        char *caso = "repetido";
        TGrafo *g = cria("bartho", 3, COM_COR);
        g = insere(g, "carlinhos", 1, SEM_COR);
        g = insere(g, "catarina", 1, SEM_COR);
        insere_aresta(g, "bartho", "carlinhos");
        insere_aresta(g, "carlinhos", "catarina");
        
        
        Test t = (Test){
            .esperado = 0,
            .grafo = g};
        
        assert(nao_tem_mesma_cor(t.grafo) == t.esperado);
    }
}

int main()
{
    testes();
}
