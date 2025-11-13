#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 1000

typedef struct {
    int N;
    double Time;
} Data;

int read_data(const char *filename, Data *data) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error: no se pudo abrir %s\n", filename);
        return -1;
    }

    int i = 0;
    char line[256];
    // Saltar la primera línea (cabecera)
    fgets(line, sizeof(line), f);

    while (fscanf(f, "%d %lf", &data[i].N, &data[i].Time) == 2) {
        // Saltar el resto de columnas en la línea
        fgets(line, sizeof(line), f);
        i++;
        if (i >= MAX_ROWS) break;
    }

    fclose(f);
    return i; // número de líneas leídas
}

int main() {
    Data median[MAX_ROWS], median_avg[MAX_ROWS], median_stat[MAX_ROWS];
    int n1, n2, n3;

    n1 = read_data("median.txt", median);
    n2 = read_data("median_avg.txt", median_avg);
    n3 = read_data("median_stat.txt", median_stat);

    if (n1 <= 0 || n2 <= 0 || n3 <= 0) {
        fprintf(stderr, "Error leyendo los archivos de datos.\n");
        return EXIT_FAILURE;
    }

    FILE *out = fopen("quick_comparison.csv", "w");
    if (!out) {
        fprintf(stderr, "Error: no se pudo crear el fichero de salida.\n");
        return EXIT_FAILURE;
    }

    fprintf(out, "N,Time_median,Time_median_avg,Time_median_stat\n");
    int n = (n1 < n2 ? (n1 < n3 ? n1 : n3) : (n2 < n3 ? n2 : n3));
    for (int i = 0; i < n; i++) {
        fprintf(out, "%d,%.6f,%.6f,%.6f\n",
                median[i].N, median[i].Time, median_avg[i].Time, median_stat[i].Time);
    }

    fclose(out);
    printf("Datos combinados guardados en quick_comparison.csv\n");
    printf("Usa este CSV en gnuplot o matplotlib para graficar.\n");

    return EXIT_SUCCESS;
}
