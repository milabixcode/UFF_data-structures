#include <stdio.h>
#include <assert.h>

#include "metadados.c"
#include "no_interno.c"

void imprime_arquivos()
{
    int i;
    // Imprime arquivo de metadados
    FILE *arq_m = fopen("metadados.dat", "rb");
    TMetadados *m = le_metadados(arq_m);
    printf("*** Arquivo de Metadados ***\n");
    imprime_metadados(m);
    fclose(arq_m);

    // Imprime arquivo de índice (nós internos da árvore)
    // A leitura não segue ordem específica -- os nós são lidos na ordem em que foram gravados no arquivo
    FILE *arq_i = fopen("indice.dat", "rb");
    printf("\n\n*** Arquivo de Indice ***\n");
    i = 0;
    TNoInterno *ni = le_no_interno(m->d, arq_i);
    while (ni != NULL)
    {
        printf("(((Endereco %d)))\n", i * tamanho_no_interno(m->d));
        imprime_no_interno(m->d, ni);
        ni = le_no_interno(m->d, arq_i);
        i += 1;
    }
    fclose(arq_i);

    // Imprime arquivo de dados (nós folha da árvore)
    // A leitura não segue ordem específica -- os nós são lidos na ordem em que foram gravados no arquivo
    FILE *arq_d = fopen("clientes.dat", "rb");
    printf("\n*** Arquivo de Dados ***\n");
    i = 0;
    TNoFolha *nf = le_no_folha(m->d, arq_d);
    while (nf != NULL)
    {
        printf("(((Endereco %d)))\n", i * tamanho_no_folha(m->d));
        imprime_no_folha(m->d, nf);
        nf = le_no_folha(m->d, arq_d);
        i += 1;
    }
    fclose(arq_d);
}

int busca_no_proximo_interno(int chave, int d, int endereco, FILE *interno_file);

int encontra_endereco(int chave, int d, TNoInterno *interno, FILE *interno_file)
{
    if (interno->chaves[0] > chave)
    {
        return busca_no_proximo_interno(chave, d, interno->p[0], interno_file);
    }

    for (int i = 0; i < interno->m; i++)
    {
        int atual = interno->chaves[i];

        if (atual == chave)
        {
            if (interno->aponta_folha)
            {
                return interno->p[i + 1];
            }
            else
            {
                return busca_no_proximo_interno(chave, d, interno->p[i + 1], interno_file);
            }
        }

        if (atual > chave)
        {
            if (interno->aponta_folha)
            {
                return interno->p[i];
            }
            else
            {
                return busca_no_proximo_interno(chave, d, interno->p[i], interno_file);
            }
        }
    }

    if (interno->aponta_folha)
    {
        return interno->p[interno->m];
    }

    return busca_no_proximo_interno(chave, d, interno->p[interno->m], interno_file);
}

int busca_no_proximo_interno(int chave, int d, int endereco, FILE *interno_file)
{
    assert(endereco != 0);
    fseek(interno_file, endereco, SEEK_SET);
    TNoInterno *prox = le_no_interno(d, interno_file);
    imprime_no_interno(d, prox);
    return encontra_endereco(chave, d, prox, interno_file);
}

/*
 * Executa busca em Arquivos utilizando Arvore B+
 * Assumir que ponteiros para NULL têm valor -1
 *
 * chave: chave do cliente que esta sendo buscado
 * nome_arquivo_metadados: nome do arquivo binário que contem os metadados
 * nome_arquivo_indice: nome do arquivo binário de indice (que contem os nohs internos da arvore B+)
 * nome_arquivo_dados: nome do arquivo binário de dados (que contem as folhas da arvore B+)
 *
 * Retorna ponteiro para nó em que a chave está ou deveria estar
 */
int busca(int chave, char *nome_arquivo_metadados, char *nome_arquivo_indice, char *nome_arquivo_dados)
{
    FILE *meta_file = fopen(nome_arquivo_metadados, "rb");
    FILE *folha_file = fopen(nome_arquivo_dados, "rb");
    FILE *interno_file = fopen(nome_arquivo_indice, "rb");

    TMetadados *meta = le_metadados(meta_file);

    if (meta->raiz_folha)
    {
        fseek(folha_file, meta->pont_raiz, SEEK_SET);
        TNoFolha *raiz = le_no_folha(meta->d, folha_file);
        imprime_no_folha(meta->d, raiz);

        return meta->pont_raiz;
    }
    else
    {
        fseek(interno_file, meta->pont_raiz, SEEK_SET);
        TNoInterno *raiz = le_no_interno(meta->d, interno_file);
        imprime_no_interno(meta->d, raiz);

        int endereco = encontra_endereco(chave, meta->d, raiz, interno_file);
        fseek(folha_file, endereco, SEEK_SET);
        TNoFolha *no_final = le_no_folha(meta->d, folha_file);
        imprime_no_folha(meta->d, no_final);
        return endereco;
    }
}

int main()
{
    // Descomente essa linha de código caso deseje imprimir o conteúdo dos arquivos de entrada para analisar
    // o comportamento da sua implementação

    // imprime_arquivos();

    /* Le chave a ser buscada */
    int chave;

    scanf("%d", &chave);

    // Chama função de busca
    int pont = busca(chave, "metadados.dat", "indice.dat", "clientes.dat");

    // Imprime resultado da função
    printf("RESULTADO DA BUSCA: %d", pont);
}
