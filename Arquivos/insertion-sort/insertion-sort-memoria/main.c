#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Funcionario {
    int cod;
    char nome[50];
    double salario;
} TFunc;

// Imprime funcionario
void imprime(TFunc *func) {
    printf("**********************************************");
    printf("\nFuncionario de código ");
    printf("%d", func->cod);
    printf("\nNome: ");
    printf("%s", func->nome);
    printf("\nSalário: ");
    printf("%4.2f", func->salario);
    printf("\n**********************************************");
}

/*
 * Cria funcionario
 */
TFunc *funcionario(int cod, char *nome, double salario) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    //inicializa espaço de memória com ZEROS
    if (func) memset(func, 0, sizeof(TFunc));
    //copia valores para os campos de func
    func->cod = cod;
    strcpy(func->nome, nome);
    func->salario = salario;
    return func;
}

/*
 * Salva funcionario no arquivo out, na posicao atual do cursor
 */
void salva(TFunc *func, FILE *out) {
    fwrite(&func->cod, sizeof(int), 1, out);
    //func->nome ao invés de &func->nome, pois string já é ponteiro
    fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
    fwrite(&func->salario, sizeof(double), 1, out);
}

/*
 * Le um funcionario do arquivo in na posicao atual do cursor
 * Retorna um ponteiro para funcionario lido do arquivo
 */
TFunc *le(FILE *in) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if (0 >= fread(&func->cod, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(&func->salario, sizeof(double), 1, in);
    return func;
}

/*
 * Imprime arquivo
 */
void imprime_arquivo(FILE *arq) {
    //le o arquivo e coloca no vetor
    rewind(arq); //posiciona cursor no inicio do arquivo
    TFunc *f = le(arq);
    int i = 0;
    while (!feof(arq)) {
        imprime(f);
        f = le(arq);
    }
}

/*
 * Retorna tamanho do registro de funcionario em bytes
 */
int tamanho_registro() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(double); //salario
}

int tamanho_arquivo(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanho_registro());
    return tam;
}

/*
 * Insere funcionários no arquivo e
 */
void insere_funcionarios(FILE *out) {
    TFunc *f;
    f = funcionario(143, "Ana Bueno", 1500);
    salva(f, out);
    f = funcionario(254, "Arnaldo Souza", 4300);
    salva(f, out);
    f = funcionario(123, "Carlos Albuquerque", 1500);
    salva(f, out);
    f = funcionario(102, "Joao Silva", 1000);
    salva(f, out);
    f = funcionario(410, "Guilherme Santos", 2000);
    salva(f, out);
    f = funcionario(305, "Marisa Clara", 5000);
    salva(f, out);
    f = funcionario(502, "Tatiana Andrade", 2500);
    salva(f, out);
    f = funcionario(200, "Caio Gusmão", 4000);
    salva(f, out);
    f = funcionario(239, "Bianca Amarilo", 3000);
    salva(f, out);
    f = funcionario(403, "Bruno Simão", 4500);
    salva(f, out);
    free(f);
}

/*
 * arq é o ponteiro para o arquivo
 * tam é a quantidade de registros que o arquivo contém
 */
void insertion_sort(FILE *arq, int tam) {
    TFunc *v[tam - 1];
    //le o arquivo e coloca no vetor
    rewind(arq); //posiciona cursor no inicio do arquivo
    TFunc *f = le(arq);
    int i = 0;
    while (!feof(arq)) {
        v[i] = f;
        f = le(arq);
        i++;
    }
    //faz o insertion sort
    for (int j = 1; j < tam; j++) {
        TFunc *f = v[j];
        i = j - 1;
        while ((i >= 0) && (v[i]->cod > f->cod)) {
            v[i + 1] = v[i];
            i = i - 1;
        }
        v[i+1] = f;
    }
    //grava vetor no arquivo, por cima do conteúdo anterior
    rewind(arq);
    for (int i = 0; i < tam; i++) {
        salva(v[i], arq);
    }
    //descarrega o buffer para ter certeza que dados foram gravados
    fflush(arq);

}

int main() {
    //declara ponteiro para arquivo
    FILE *arq;
    //abre arquivo para leitura e escrita
    if ((arq = fopen("funcionario.dat", "wb+")) == NULL) {
        printf("Erro ao abrir arquivo\n");
    } else {
        //insere funcionários
        insere_funcionarios(arq);
        //força flush para salvar funcionários
        fflush(arq);
        imprime_arquivo(arq);
        insertion_sort(arq, tamanho_arquivo(arq));
        printf("\n\nArquivo apos ordenacao...\n\n");
        imprime_arquivo(arq);
        fclose(arq);
    }
}
