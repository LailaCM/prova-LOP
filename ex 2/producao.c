#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_MACHINES 4
#define MAX_DAYS 31

int main() {
	setlocale(LC_ALL, "Portuguese");
    int machines[MAX_MACHINES] = {0};
    int daily_production[MAX_DAYS][MAX_MACHINES] = {0};
    FILE *file = fopen("producao.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo producao.csv\n");
        return 1;
    }

    char buffer[100];
    fgets(buffer, sizeof(buffer), file);

    int day, machine, i = 0;
    while (fscanf(file, "%d/%*d/%*d;%*[^;];%d\n", &day, &machine) == 2) {
        machines[machine - 1]++;
        daily_production[day - 1][machine - 1]++;
        i++;
    }
    
    fclose(file);

    printf("Quantidade de explosivos produzidos por máquina:\n");
    for (i = 0; i < MAX_MACHINES; i++) {
        printf("Máquina %d: %d\n", i + 1, machines[i]);
    }
    printf("\n");

    file = fopen("explosivos.md", "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo explosivos.md\n");
        return 1;
    }

    fprintf(file, "| Data       | Maquina 1 | Maquina 2 | Maquina 3 | Maquina 4 |\n");
    fprintf(file, "|------------|------------|------------|------------|------------|\n");

    for (i = 0; i < MAX_DAYS; i++) {
        fprintf(file, "| %02d/05/2024 | %10d | %10d | %10d | %10d |\n", i + 1,
                daily_production[i][0], daily_production[i][1], daily_production[i][2], daily_production[i][3]);
    }

    fclose(file);

    printf("Relatório salvo com sucesso em explosivos.md\n");

    return 0;
}
