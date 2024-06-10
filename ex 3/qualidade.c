#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <limits.h>

#define MAX_PRODUTOS 100

typedef struct {
    int numero_de_serie;
    int resistencia;
    int durabilidade;
} Produto;

int main() {
    int i;
    setlocale(LC_ALL, "Portuguese"); // Define a codificação de caracteres

    FILE *arquivo;
    Produto produtos[MAX_PRODUTOS];
    int num_produtos = 0;
    int soma_resistencia = 0, soma_durabilidade = 0;
    int resistencia_max = 0, resistencia_min = INT_MAX; // Inicializa com valor máximo possível
    int durabilidade_max = 0, durabilidade_min = INT_MAX; // Inicializa com valor máximo possível
    int acima_media = 0, abaixo_media = 0;

    // Abre o arquivo para leitura
    arquivo = fopen("parametros.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê os dados do arquivo
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char *token = strtok(linha, ";");
        if (token!= NULL) {
            produtos[num_produtos].numero_de_serie = atoi(token);
            token = strtok(NULL, ";");
            produtos[num_produtos].resistencia = atoi(token);
            token = strtok(NULL, ";");
            produtos[num_produtos].durabilidade = atoi(token);

            // Atualiza as somas
            soma_resistencia += produtos[num_produtos].resistencia;
            soma_durabilidade += produtos[num_produtos].durabilidade;

            // Atualiza os valores máximos
            if (produtos[num_produtos].resistencia > resistencia_max) {
                resistencia_max = produtos[num_produtos].resistencia;
            }
            if (produtos[num_produtos].durabilidade > durabilidade_max) {
                durabilidade_max = produtos[num_produtos].durabilidade;
            }

            // Atualiza os valores mínimos
            if (produtos[num_produtos].resistencia < resistencia_min) {
                resistencia_min = produtos[num_produtos].resistencia;
            }
            if (produtos[num_produtos].durabilidade < durabilidade_min) {
                durabilidade_min = produtos[num_produtos].durabilidade;
            }

            num_produtos++;
        }
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Verifica se há produtos para calcular as médias
    if (num_produtos == 0) {
        printf("Nenhum produto encontrado.\n");
        return 1;
    }

    // Calcula as médias
    float media_resistencia = (float)soma_resistencia / num_produtos;
    float media_durabilidade = (float)soma_durabilidade / num_produtos;

    // Abre o arquivo para escrita
    arquivo = fopen("qualidade.md", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo qualidade.md\n");
        return 1;
    }

    // Escreve os resultados no arquivo qualidade.md
    fprintf(arquivo, "# Analise de Qualidade\n\n");
    fprintf(arquivo, "## Medias\n");
    fprintf(arquivo, "- Media de resistencia: %.2f\n", media_resistencia);
    fprintf(arquivo, "- Media de durabilidade: %.2f\n\n", media_durabilidade);

    fprintf(arquivo, "## Produtos com Maior e Menor Resistencia\n");
    fprintf(arquivo, "- Produto com maior resistencia: %d\n", resistencia_max);
    fprintf(arquivo, "- Produto com menor resistencia: %d\n\n", resistencia_min);

    fprintf(arquivo, "## Produtos com Maior e Menor Durabilidade\n");
    fprintf(arquivo, "- Produto com maior durabilidade: %d\n", durabilidade_max);
    fprintf(arquivo, "- Produto com menor durabilidade: %d\n\n", durabilidade_min);

    // Conta quantos produtos estão acima e abaixo das médias
    for (i = 0; i < num_produtos; i++) {
        if (produtos[i].resistencia > media_resistencia && produtos[i].durabilidade > media_durabilidade) {
            acima_media++;
        } else if (produtos[i].resistencia < media_resistencia && produtos[i].durabilidade < media_durabilidade) {
            abaixo_media++;
        }
    }

    // Escreve o resultado final no arquivo qualidade.md
    fprintf(arquivo, "Ha %s produtos acima das medias do que abaixo.\n", (acima_media > abaixo_media) ? "mais" : ((acima_media < abaixo_media) ? "menos" : "a mesma quantidade de"));
    
    // Fecha o arquivo
    fclose(arquivo);

    return 0;
}

