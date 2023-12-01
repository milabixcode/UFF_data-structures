#include <limits.h>
#include <stdio.h>

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

// método da dobra
int dobra(int t, int n, int chave)
{
    char valor[n];
    int digito;
    //converte a chave para uma string pra poder acessar cada posição do 'numero'
    sprintf(valor, "%d", chave);
    //a dobra acontece de de t em t
    for (int i = 0; i < n; i += t)
    {
        for (int j = 0; j < t; j++)
        {
            digito = valor[i + j] + valor[i + 2*t -1-j];
            digito = digito % 10;
            valor[i+ 2*t-1-j] = digito;
        }                
    }
}

/* Executa busca em Arquivos por Encadeamento Exterior (Hash)
 * Assumir que ponteiro para proximo noh eh igual a -1 quando nao houver proximo noh
 * Ponteiros são lógicos (é preciso multiplicar pelo tamanho do registro para calcular o valor do deslocamento
 * Use a função tamanho_compartimento() e tamanho_cliente() dependendo do arquivo que está sendo manipulado
 *
 * Parametros:
 * cod_cli: chave do cliente que esta sendo buscado
 * nome_arquivo_hash: nome do arquivo que contem a tabela hash
 * nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
 * m: tamanho da tabela hash (a função de hash é h(x) = x mod m
 *
 * Retorna o endereco (lógico) onde o cliente foi encontrado, ou -1 se nao for encontrado
 */
int busca(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m)
{
    // Calculo de endereço logico
    int h = hash(cod_cli);
    // abro os arquivos de hash e dados
    FILE *arquivo_hash = fopen(nome_arquivo_hash, "r+");
    FILE *arquivo_dados = fopen(nome_arquivo_dados, "r+");

    // Pego o ponteiro da posição em que o cliente deveria estar
    fseek(arquivo_hash, tamanho_compartimento() * h, SEEK_SET);
    TCompartimento *p = le_compartimento(arquivo_hash);

    // se não existe lista encadeada associada aquele ponteiro
    // retorno -1
    if (p->prox == -1)
    {
        fclose(arquivo_dados);
        fclose(arquivo_hash);
        return -1;
    }
    // se existe lista encadeada
    else
    {
        // p->prox: endereço logico
        // tamanho_cliente()*p->prox: endereço fisico
        fseek(arquivo_dados, (p->prox) * tamanho_cliente(), SEEK_SET);
        TCliente *cliente = le_cliente(arquivo_dados);
        imprime_cliente(cliente);

        // enquanto eu nao chego no cliente ou o final da lista
        // ando no meu arquivo um cliente
        while ((cliente->cod != cod_cli) && (cliente->prox != -1))
        {
            int end_logico = cliente->prox;
            fseek(arquivo_dados, end_logico * tamanho_cliente(), SEEK_SET);
            cliente = le_cliente(arquivo_dados);
            imprime_cliente(cliente);
        }
        // se eu achei o cliente
        // retorno o endereço logico dele
        if (cliente->cod == cod_cli)
        {
            if (cliente->ocupado == 0)
            {
                fclose(arquivo_dados);
                fclose(arquivo_hash);
                return -1;
            }
            else
            {
                int end_logico = (ftell(arquivo_dados) / tamanho_cliente()) - 1;
                fclose(arquivo_dados);
                fclose(arquivo_hash);
                return end_logico;
            }
        }
        // se o cliente não está na lista
        // retorno -1
        else
        {
            fclose(arquivo_dados);
            fclose(arquivo_hash);
            return -1;
        }
    }
}

int main()
{
    /* Essa função gera a saída que é usada no teste do run.codes. Ela NÃO DEVE SER MODIFICADA */
    int cod;
    int pont;

    // Imprime arquivos de entrada
    // imprime_arquivos("tabHash.dat", "clientes.dat");

    // le chave a ser buscada
    scanf("%d", &cod);
    printf("REGISTROS ACESSADOS:\n");
    pont = busca(cod, "tabHash.dat", "clientes.dat", M);

    // Imprime resultado da função
    printf("RESULTADO: %d", pont);
}