#include <stdio.h>

void imprime_arquivo(char *nomeArq){
    FILE *arq; //declara ponteiro para arquivo
    //abre arquivo para leitura
    arq = fopen(nomeArq, "r");
    if (arq != NULL){// checa se não deu erro na abertura do arquivo
        char s[10];
        fscanf(arq, "%s", s);
        while (!feof(arq)) {//testa se chegou ao final do arquivo
            printf("%s\n", s);
            fscanf(arq, "%s", s);
        }
        fclose(arq); //fecha arquivo
    }
    else printf("Erro ao abrir arquivo\n");
}

void merge(char *nomeArq1, char *nomeArq2, char *nomeArqMerge) {
    FILE *arq1;
    FILE *arq2;
    FILE *arq_saida;

    arq1 = fopen(nomeArq1, "r");
    arq2 = fopen(nomeArq2, "r");
    arq_saida = fopen(nomeArqMerge, "w");

    int valor_arq1;
    int valor_arq2;
    // leio os arquivos
    int continuar_arq1 = fscanf(arq1, "%d", &valor_arq1);
    int continuar_arq2 = fscanf(arq2, "%d", &valor_arq2);
    while (continuar_arq1 != EOF && continuar_arq2 != EOF)
    {
        if (valor_arq1 == valor_arq2)
        {
            fprintf(arq_saida, "%d\n", valor_arq1);
            continuar_arq1 = fscanf(arq1, "%d", &valor_arq1);
            continuar_arq2 = fscanf(arq2, "%d", &valor_arq2);
        }
        else if (valor_arq1 < valor_arq2)
        {
            fprintf(arq_saida, "%d\n", valor_arq1);
            continuar_arq1 = fscanf(arq1, "%d", &valor_arq1);
        }
        else
        {
            fprintf(arq_saida, "%d\n", valor_arq2);
            continuar_arq2 = fscanf(arq2, "%d", &valor_arq2);
        }
    }
    while (continuar_arq1 != EOF)
    {
        fprintf(arq_saida, "%d\n", valor_arq1);
        continuar_arq1 = fscanf(arq1, "%d", &valor_arq1);
    }
    while (continuar_arq2 != EOF)
    {
        fprintf(arq_saida, "%d\n", valor_arq2);
        continuar_arq2 = fscanf(arq2, "%d", &valor_arq2);
    }

    fprintf(arq_saida, "\n");

    fclose(arq1);
    fclose(arq2);
    fclose(arq_saida);
}

int main(int argc, char **argv) {
    merge("numeros1.txt", "numeros2.txt", "merge.txt");
    imprime_arquivo("merge.txt");
}
