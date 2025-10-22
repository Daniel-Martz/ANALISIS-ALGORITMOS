#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ERR -1

/***************************************************/
/* Function: InsertSort   Date: 17/10/2025         */
/***************************************************/
int InsertSort(int *array, int ip, int iu) {
    int i, j, OB = 0, aux;
    
    if (array == NULL || ip < 0 || iu < 0 || ip > iu) return ERR;

    for (i = ip + 1; i <= iu; i++)
    {
      aux = array[i];
      j = i - 1;
      while (j >= ip && array[j] > aux)
      {
        array[j + 1] = array[j];
        OB++;
        j--;
      }
      if (j >= ip) OB++;
      array[j + 1] = aux;
    }
  
    return OB;
}

/***************************************************/
/* Function: BubbleSort    Date: 17/10/2025        */
/***************************************************/
int BubbleSort(int *array, int ip, int iu) {
    int flag = 1;
    int i = iu, j = 0;
    int aux = 0, OB = 0;

    if (array == NULL || ip < 0 || iu < 0 || ip > iu) return ERR;
    
    while ((flag == 1) && (i > ip)) {
        flag = 0;
        for (j = ip; j < i; j++) {
            if (array[j] > array[j + 1]) {
                aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
                flag = 1;
            }
            OB++;
        }
        i--;
    }
    return OB;
}

/***************************************************/
/* Generación de arrays                            */
/***************************************************/
void genera_mejor(int *array, int n) {
    for (int i = 0; i < n; i++)
        array[i] = i;
}

void genera_peor(int *array, int n) {
    for (int i = 0; i < n; i++)
        array[i] = n - i;
}

/***************************************************/
/* Función principal                               */
/***************************************************/
int main() {
    FILE *fout;
    int *array;
    clock_t start, end;
    double t_insert_best, t_bubble_best, t_insert_worst, t_bubble_worst;
    int N;

    fout = fopen("tiempos_sorts.dat", "w");
    if (!fout) {
        fprintf(stderr, "Error al abrir el fichero de salida.\n");
        return -1;
    }

    fprintf(fout, "# N\tTInsert_Best\tTBubble_Best\tTInsert_Worst\tTBubble_Worst\n");

    for (N = 1000; N <= 100000; N += 1000) {
        array = (int *) malloc(N * sizeof(int));
        if (!array) {
            fprintf(stderr, "Error al reservar memoria.\n");
            fclose(fout);
            return -1;
        }

        /* Mejor caso (array ordenado ascendente) */
        genera_mejor(array, N);
        start = clock();
        InsertSort(array, 0, N - 1);
        end = clock();
        t_insert_best = ((double)(end - start)) / CLOCKS_PER_SEC;

        genera_mejor(array, N);
        start = clock();
        BubbleSort(array, 0, N - 1);
        end = clock();
        t_bubble_best = ((double)(end - start)) / CLOCKS_PER_SEC;

        /* Peor caso (array ordenado descendente) */
        genera_peor(array, N);
        start = clock();
        InsertSort(array, 0, N - 1);
        end = clock();
        t_insert_worst = ((double)(end - start)) / CLOCKS_PER_SEC;

        genera_peor(array, N);
        start = clock();
        BubbleSort(array, 0, N - 1);
        end = clock();
        t_bubble_worst = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fout, "%d\t%.6f\t%.6f\t%.6f\t%.6f\n",
                N, t_insert_best, t_bubble_best, t_insert_worst, t_bubble_worst);

        free(array);
    }

    fclose(fout);
    printf("Fichero 'tiempos_sorts.dat' generado correctamente.\n");
    return 0;
}
