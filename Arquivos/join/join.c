#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TAM_NOME 100

typedef struct Departamento
{
    int cod_dept;
    int sala;
    char nome[TAM_NOME];
} TDepartamento;

typedef struct Funcionario
{
    int cod_func;
    int cod_dept;
    char nome[TAM_NOME];
} TFuncionario;

void salva_departamento(TDepartamento *dept, FILE *out)
{
    fprintf(out, "%d", dept->cod_dept);
    fprintf(out, "%c", ';');
    fprintf(out, "%d", dept->sala);
    fprintf(out, "%c", ';');
    fprintf(out, "%s", dept->nome);
    fprintf(out, "%c", ';');
    fprintf(out, "%s", "\n");
}

void salva_funcionario(TFuncionario *func, FILE *out)
{
    fprintf(out, "%d", func->cod_func);
    fprintf(out, "%c", ';');
    fprintf(out, "%d", func->cod_dept);
    fprintf(out, "%c", ';');
    fprintf(out, "%s", func->nome);
    fprintf(out, "%c", ';');
    fprintf(out, "%s", "\n");
}

TFuncionario *le_funcionario(FILE *in)
{
    TFuncionario *func = (TFuncionario *)malloc(sizeof(TFuncionario));
    char linha[150];
    if (fgets(linha, 150, in) == NULL)
    {
        free(func);
        return NULL;
    }

    char delimitador[] = ";";
    char *ptr;
    int cod;

    // quebra a linha
    ptr = strtok(linha, delimitador);
    cod = atoi(ptr);
    func->cod_func = cod;
    ptr = strtok(NULL, delimitador);
    cod = atoi(ptr);
    func->cod_dept = cod;
    ptr = strtok(NULL, delimitador);
    strcpy(func->nome, ptr);

    return func;
}

TDepartamento *le_departamento(FILE *in)
{
    TDepartamento *dept = (TDepartamento *)malloc(sizeof(TDepartamento));
    char linha[150];
    if (fgets(linha, 150, in) == NULL)
    {
        free(dept);
        return NULL;
    }

    char delimitador[] = ";";
    char *ptr;
    int cod, sala;

    // quebra a linha
    ptr = strtok(linha, delimitador);
    cod = atoi(ptr);
    dept->cod_dept = cod;
    ptr = strtok(NULL, delimitador);
    sala = atoi(ptr);
    dept->sala = sala;
    ptr = strtok(NULL, delimitador);
    strcpy(dept->nome, ptr);

    return dept;
}

void imprime_arquivo(char *name)
{
    FILE *arq; // declara ponteiro para arquivo
    // abre arquivo para leitura
    arq = fopen(name, "r");
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

void join(char *nome_arq_dept, char *nome_arq_funcionarios, char *nome_arq_join)
{
    FILE *arquivo_depart;
    FILE *arquivo_funcionarios;
    FILE *arq_join;

    arquivo_depart = fopen(nome_arq_dept, "r");
    arquivo_funcionarios = fopen(nome_arq_funcionarios, "r");
    arq_join = fopen(nome_arq_join, "w");

    TDepartamento *depart = le_departamento(arquivo_depart);

    while (depart != NULL)
    {
        TFuncionario *func = le_funcionario(arquivo_funcionarios);
        while (func != NULL)
        {
            if (func->cod_dept == depart->cod_dept)
            {
                fprintf(arq_join, "%d;%d;%s;", depart->cod_dept, depart->sala, depart->nome);
                fprintf(arq_join, "%d;%s;\n", func->cod_func, func->nome);
            }

            func = le_funcionario(arquivo_funcionarios);
        }
        fseek(arquivo_funcionarios, 0, SEEK_SET);

        depart = le_departamento(arquivo_depart);
    }
    fclose(arquivo_depart);
    fclose(arquivo_funcionarios);
    fclose(arq_join);
}

int main()
{
    join("departamentos.txt", "funcionarios.txt", "join.txt");
    imprime_arquivo("join.txt");
}
