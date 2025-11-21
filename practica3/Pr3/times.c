/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "search.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

short generate_search_times(pfunc_search method, pfunc_key_generator generator,
                            int order, char *file, int num_min, int num_max, int incr, int n_times)
{
    int i, n_intervals,N;
    PTIME_AA ptime = NULL;

    /*Comprobación de errores*/
    if ((method == NULL) || (generator == NULL) || (file == NULL) ||
        (order != SORTED && order != NOT_SORTED) ||
        (num_min > num_max) || (n_times <= 0) || (incr <= 0))
    {
        fprintf(stderr, "Las variables introducidas no son válidas.\n");
        return ERR;
    }

    /*Calcular cuántos tamaños de diccionario vamos a probar*/
    n_intervals = ((num_max - num_min) / incr) + 1;
    ptime = (PTIME_AA)calloc(n_intervals, sizeof(TIME_AA));
    if (ptime == NULL)
    {
        fprintf(stderr, "Error al reservar memoria  .\n");
        return ERR;
    }

    for (i = 0; i < n_intervals; i++)
    {
        N = num_min + i * incr;
        if (average_search_time(method, generator, order, N, n_times, &ptime[i]) == ERR)
        {
            fprintf(stderr, "Error en la funcion average_search_time\n");
            free(ptime);
            return ERR;
        }
    }

    /*Guardar los resultados en el fichero*/
    if (save_time_table(file, ptime, n_intervals) == ERR)
    {
        fprintf(stderr, "Error al guardar la tabla de tiempos.\n");
        free(ptime);
        return ERR;
    }
    free(ptime);
    return OK;
}

short save_time_table(char *file, PTIME_AA ptime, int N)
{
    FILE *fout = NULL;
    int i;

    if (file == NULL || ptime == NULL || N <= 0)
    {
        return ERR;
    }

    if (!(fout = fopen(file, "w")))
    {
        fprintf(stderr, "Error al abrir el fichero");
        return ERR;
    }

    fprintf(fout, "%-6s %-12s %-14s %-8s %-8s\n", "N", "Time", "Average_OB", "Max_OB", "Min_OB");

    for (i = 0; i < N; i++)
    {
        fprintf(fout, "%-6i %-12.6f %-14.2f %-8i %-8i\n",
                ptime[i].N,
                ptime[i].time,
                ptime[i].average_ob,
                ptime[i].max_ob,
                ptime[i].min_ob);
    }
    fclose(fout);
    return OK;
}
