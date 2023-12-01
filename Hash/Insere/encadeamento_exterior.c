#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "cliente.c"
#include "compartimento_hash.c"

#define M 7

void imprime_arquivos(char *nome_arquivo_hash, char *nome_arquivo_dados)
{
    // Imprime arquivo de hash
    printf("TABELA HASH:\n");
    imprime_arquivo_hash(nome_arquivo_hash);

    // Imprime arquivo de dados
    printf("\nDADOS:\n");
    imprime_arquivo_dados(nome_arquivo_dados);
}

int hash(int cod_cli)
{
    return cod_cli % M;
}

/* Executa insercao em Arquivos por Encadeamento Exterior (Hash)
 * cod_cli: chave do cliente que esta sendo inserido
 * nome_cli: nome do cliente a ser inserido
 * nome_arquivo_hash: nome do arquivo que contem a tabela hash
 * nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
 * Retorna o endereco (lógico) onde o cliente foi inserido, ou -1 se nao conseguiu inserir
 */
int insere(int cod_cli, char *nome_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m)
{
    TCliente *novo_cliente = cliente(cod_cli, nome_cli, -1, 1);

    // Cálculo do hash (endereço)
    int h = hash(cod_cli);
    // Abro arquivo hash
    FILE *arquivo_hash = fopen(nome_arquivo_hash, "r+");
    // Pego o ponteiro dessa posição
    fseek(arquivo_hash, tamanho_compartimento() * h, SEEK_SET);
    TCompartimento *p = le_compartimento(arquivo_hash);
    // Abro arquivo cliente
    FILE *arquivo_dados = fopen(nome_arquivo_dados, "r+");
    // Checo se existe algum cliente na posição
    if (p->prox == -1)
    {
        fseek(arquivo_dados, 0, SEEK_END);
        salva_cliente(novo_cliente, arquivo_dados);
        fseek(arquivo_hash, -tamanho_compartimento(), SEEK_CUR);
        p->prox = (ftell(arquivo_dados) / tamanho_cliente()) - 1;
        salva_compartimento(p, arquivo_hash);

        fclose(arquivo_dados);
        fclose(arquivo_hash);
        return p->prox;
    }
    // Pego a posição do dado
    fseek(arquivo_dados, tamanho_cliente() * (p->prox), SEEK_SET);
    TCliente *cliente = le_cliente(arquivo_dados);

    int posicao_livre = -1;
    if (cliente->ocupado == 0)
    {
        posicao_livre = ftell(arquivo_dados) - tamanho_cliente();
    }

    // Busco registro na lista encadeada associada ao h
    while (cliente->prox != -1 && cliente->cod != cod_cli)
    {
        // se cliente OCUPADO
        if (cliente->ocupado == 1)
        {
            fseek(arquivo_dados, tamanho_cliente() * cliente->prox, SEEK_SET);
            cliente = le_cliente(arquivo_dados);
        }
        // se cliente LIBERADO
        else
        {
            if (posicao_livre == -1)
            {
                posicao_livre = ftell(arquivo_dados) - tamanho_cliente();
            }
            fseek(arquivo_dados, tamanho_cliente() * cliente->prox, SEEK_SET);
            cliente = le_cliente(arquivo_dados);
        }


        // end fisico = end logico *tamanho
    }
    // se cliente foi encontrado
    // gravo cliente na posiçao anterior a cliente->prox
    if (cliente->cod == cod_cli && cliente->ocupado == 1)
    {
        fclose(arquivo_dados);
        fclose(arquivo_hash);
        return -1;
    }
    else
    {
        if (posicao_livre != -1)
        {
            fseek(arquivo_dados, posicao_livre, SEEK_SET);
            cliente = le_cliente(arquivo_dados);
            novo_cliente->prox = cliente->prox;
            fseek(arquivo_dados, posicao_livre, SEEK_SET);
            salva_cliente(novo_cliente, arquivo_dados);
            int retorno = (ftell(arquivo_dados) / tamanho_cliente()) - 1;

            fclose(arquivo_dados);
            fclose(arquivo_hash);
            return retorno;
        }

        if (cliente->ocupado == 1)
        {
            int posicao_anterior = ftell(arquivo_dados) - tamanho_cliente();
            fseek(arquivo_dados, 0, SEEK_END);
            salva_cliente(novo_cliente, arquivo_dados);
            int retorno = (ftell(arquivo_dados) / tamanho_cliente()) - 1;
            cliente->prox = retorno;
            fseek(arquivo_dados, posicao_anterior, SEEK_SET);
            salva_cliente(cliente, arquivo_dados);

            fclose(arquivo_dados);
            fclose(arquivo_hash);
            return retorno;
        }
        else
        {
            fseek(arquivo_dados, -tamanho_cliente(), SEEK_CUR);
            salva_cliente(novo_cliente, arquivo_dados);

            int retorno = (ftell(arquivo_dados) / tamanho_cliente()) - 1;

            fclose(arquivo_dados);
            fclose(arquivo_hash);
            return retorno;
        }
    }
}

int main()
{
    /* Essa função gera a saída que é usada no teste do run.codes. Ela NÃO DEVE SER MODIFICADA */
    int cod;
    char nome[TAM_NOME] = "";
    int pont;

    // le dados a serem inseridos
    scanf("%d", &cod);
    scanf("%s", nome);

    // Imprime arquivos de entrada
    // imprime_arquivos("tabHash.dat", "clientes.dat");

    pont = insere(cod, nome, "tabHash.dat", "clientes.dat", M);
    imprime_arquivos("tabHash.dat", "clientes.dat");
    // Imprime resultado da função
    printf("\nRESULTADO: %d", pont);
}