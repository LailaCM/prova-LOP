#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct{
    int matricula;
    char funcionario[50];
    char data[12];
    char origem[50];
    char destino[50];
    int distancia;
    float preco;
    float total;
    float reembolso; // Adicionado o campo de reembolso
} Viagem;

Viagem viagens[50];
int totalViagens = 0, i;
float totalReembolsoGeral = 0; // Total geral de reembolso

float calcularReembolso (float precoLitroCombustivel, int distancia){
    float reembolso = (precoLitroCombustivel * distancia) / 3.0;
    return reembolso;
}

void carregaDados(){
    FILE *arq;
    char linha[100];
    arq = fopen("viagens.csv", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    else
    {
        fgets(linha, 100, arq); // Ignorar a primeira linha
        while (fgets(linha, 100, arq) != NULL)
        {
            viagens[totalViagens].matricula = atoi(strtok(linha, ";"));
            strcpy(viagens[totalViagens].funcionario, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].data, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].origem, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].destino, strtok(NULL, ";"));
            viagens[totalViagens].distancia = atoi(strtok(NULL, ";"));
            viagens[totalViagens].preco = atof(strtok(NULL, ";"));
            viagens[totalViagens].total = viagens[totalViagens].distancia * viagens[totalViagens].preco;
            viagens[totalViagens].reembolso = calcularReembolso(viagens[totalViagens].preco, viagens[totalViagens].distancia);
            totalReembolsoGeral += viagens[totalViagens].reembolso; 
            totalViagens++;
        }
    }
    fclose(arq);
}

void mostrarDados(){
    FILE *arq_saida;
    arq_saida = fopen("RelatorioViagens.md", "w");
    if (arq_saida == NULL)
    {
        printf("Erro ao criar o arquivo de saída\n");
        return;
    }

    fprintf(arq_saida, "# Relatório de Viagens\n\n");
    fprintf(arq_saida, "| Matricula | Funcionario | Data | Origem | Destino | Distancia | Preco | Total | Reembolso |\n");
    fprintf(arq_saida, "| --------- | ----------- | ---- | ------ | ------- | --------- | ----- | ----- | --------- |\n");

    for (i = 0; i < totalViagens; i++)
    {
        fprintf(arq_saida, "| %d | %s | %s | %s | %s | %d | %.2f | %.2f | %.2f |\n",
                viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem,
                viagens[i].destino, viagens[i].distancia, viagens[i].preco, viagens[i].total, viagens[i].reembolso);
    }

    fprintf(arq_saida, "\n # Total geral de reembolso: %.2f\n", totalReembolsoGeral); 

    fclose(arq_saida);
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    carregaDados();
    mostrarDados();
    printf("Arquivo 'RelatorioViagens.md' gerado com sucesso.\n");
    return 0;
}
