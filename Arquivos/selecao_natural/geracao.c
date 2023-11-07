#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "cliente.c"

#include <limits.h>
#include <dirent.h>
#include <string.h>

typedef struct vetor
{
    TCliente *cli;
} TVet;

void imprime_arquivo(char *nome)
{
    FILE *arq; // declara ponteiro para arquivo
    // abre arquivo para leitura
    arq = fopen(nome, "r");
    if (arq != NULL)
    { // checa se não deu erro na abertura do arquivo
        char linha[150];
        fgets(linha, 150, arq);
        while (!feof(arq))
        { // testa se chegou ao final do arquivo
            printf("%s", linha);
            fgets(linha, 150, arq);
        }
        fclose(arq); // fecha arquivo
    }
    else
        printf("Erro ao abrir arquivo\n");
}

char *gera_nome_particao(int num_part)
{
    char *nome_particao = (char *)malloc(sizeof(char[10]));
    char num_particao[10];

    strcpy(nome_particao, "p");
    sprintf(num_particao, "%d", num_part);
    strcat(nome_particao, num_particao);
    strcat(nome_particao, ".txt");

    return nome_particao;
}

TCliente *acha_menor(TCliente *vetor, int tam);

int compara_cod(void *a, void *b)
{
    TCliente *x = a, *y = b;
    return x->cod_cliente - y->cod_cliente;
}

void desovar(TCliente *vetor, int tam, FILE *arquivo)
{
    qsort(vetor, tam, sizeof(TCliente), compara_cod);
    for (int i = 0; i < tam; i++)
    {
        salva_cliente(&vetor[i], arquivo);
    }
}

int selecao_natural(char *nome_arquivo_entrada, int tam_memoria)
{
    FILE *entrada = fopen(nome_arquivo_entrada, "r");
    TCliente *memoria = (TCliente *)malloc(sizeof(TCliente) * tam_memoria);
    TCliente *reservatorio = (TCliente *)malloc(sizeof(TCliente) * tam_memoria);
    int tam_reservatorio = 0;

    int num_particao = 0;
    FILE *particao = fopen(gera_nome_particao(++num_particao), "w");

    // passo 1
    for (int i = 0; i < tam_memoria; i++)
    {
        TCliente *cliente = le_cliente(entrada);
        if (!cliente)
        {
            desovar(memoria, i, particao);
            fclose(particao);
            return num_particao;
        }
        memoria[i] = *cliente;
    }

    while (1)
    {
        // passo 2
        TCliente *menor = acha_menor(memoria, tam_memoria);

        // passo 3
        salva_cliente(menor, particao);

        // passo 4
        TCliente salvo = *menor;

        while (1)
        {
            TCliente *novo = le_cliente(entrada);
            if (!novo)
            {
                *menor = memoria[tam_memoria - 1];
                desovar(memoria, tam_memoria - 1, particao);
                fclose(particao);

                if (tam_reservatorio != 0)
                {
                    particao = fopen(gera_nome_particao(++num_particao), "w");
                    desovar(reservatorio, tam_reservatorio, particao);
                    fclose(particao);
                }
                return num_particao;
            }

            if (novo->cod_cliente > salvo.cod_cliente)
            {
                *menor = *novo;
                break;
            }

            // passo 5
            reservatorio[tam_reservatorio] = *novo;
            tam_reservatorio++;

            if (tam_reservatorio < tam_memoria)
            {
                continue;
            }

            *menor = memoria[tam_memoria - 1];
            desovar(memoria, tam_memoria - 1, particao);
            fclose(particao);

            TCliente *tmp = memoria;
            memoria = reservatorio;
            reservatorio = tmp;
            tam_reservatorio = 0;

            particao = fopen(gera_nome_particao(++num_particao), "w");

            break;
        }
    }
}

TCliente *acha_menor(TCliente *vetor, int tam)
{
    TCliente *menor = &vetor[0];
    for (int i = 0; i < tam; i++)
    {
        if (vetor[i].cod_cliente < menor->cod_cliente)
        {
            menor = &vetor[i];
        }
    }
    return menor;
}

int main()
{
    int tam_memoria;
    scanf("%d", &tam_memoria);
    int num_part = selecao_natural("entrada.txt", tam_memoria);
    for (int i = 1; i < num_part + 1; i++)
    {
        printf("*** %s\n", gera_nome_particao(i));
        imprime_arquivo(gera_nome_particao(i));
    }
}