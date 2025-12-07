/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Daniel Martínez y Rodrigo Díaz-Regañón
 * Version: 1.0
 * Fecha: 23-11-2025
 *
 */

#include "times.h"
#include "search.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/**
 * @brief Subrutina para save_time_tables que guarda todos los tiempos tomados en una 
 * estructura TIME_AA en un archivo con un formáto en columnas
 * 
 * @param file Nombre del archivo donde se guardaran los tiempos
 * @param ptime Tabla de estrcuturas TIME_AA
 * @param N Número de estructuras a escribir
 * @return OK si todo va bien, ERR en caso de error 
 */
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
        fprintf(fout, "%-6i %-12.10lf %-14.2lf %-8i %-8i\n",
                ptime[i].N,
                ptime[i].time,
                ptime[i].average_ob,
                ptime[i].max_ob,
                ptime[i].min_ob);
    }

    fclose(fout);
    return OK;
}

/**
 * @brief funcion que rellena todos los campos de la estructura TIMEAA:
 * - número de permutaciones
 * - número de elementos por permutación
 * - tiempo medio en segundos
 * - número medio de OBs
 * - número mínimo de OBs
 * - número máximo de OBs
 * @param metodo Método de ordenación
 * @param generator Función que genera las claves
 * @param order Si se usan las tablas ordeandas en el TAD diccionario
 * @param N Tamaño del diccionario
 * @param n_times Número de veces que se busca cada N clave en el diccionario
 * @param ptime Puntero al diccionario
 * @return OK si todo fue bien, ERR si hay algun fallo
 */
short average_search_time(pfunc_search metodo, pfunc_key_generator generator, int order, int N, int n_times, PTIME_AA ptime)
{

    PDICT dict;
    int *perm = NULL;
    int *keys = NULL;
    int pos;
    int n_elems;
    int i, OB_aux, min_OB = -1, max_OB = -1;
    long long sum_OB = 0;
    clock_t start, end;
    double time;

    if (!metodo || !generator || (order != SORTED && order != NOT_SORTED) || N <= 0 || n_times <= 0 || !ptime)
    {
        fprintf(stderr, "Los parametros introducidos en average_search_time no son validos\n");
        return ERR;
    }

    if (!(dict = init_dictionary(N, order)))
    {
        return ERR;
    }

    if (!(perm = generate_perm(N)))
    {
        free_dictionary(dict);
        return ERR;
    }
    if (massive_insertion_dictionary(dict, perm, N) == ERR)
    {
        free_dictionary(dict);
        free(perm);
        return ERR;
    }

    n_elems = N * n_times;

    if (!(keys = (int *)calloc(n_elems, sizeof(int))))
    {
        fprintf(stderr, "Error reservando memeoria para la tabla con los N*n_times keys\n");
        free_dictionary(dict);
        free(perm);
        return ERR;
    }

    generator(keys, n_elems, N);

    start = clock();
    for (i = 0; i < n_elems; i++)
    {
        OB_aux = metodo(dict->table, 0, N - 1, keys[i], &pos);
        printf("%i ", i);

        if (OB_aux == ERR || OB_aux == NOT_FOUND || dict->table[pos] != keys[i])
        {
            printf("%i. %i", keys[i], dict->table[pos]);
            fprintf(stderr, "Error al realizar la busqueda\n");
            free_dictionary(dict);
            free(perm);
            free(keys);
            return ERR;
        }

        if (max_OB == -1)
        {
            max_OB = OB_aux;
        }
        if (min_OB == -1)
        {
            min_OB = OB_aux;
        }

        if (OB_aux > max_OB)
        {
            max_OB = OB_aux;
        }
        if (OB_aux < min_OB)
        {
            min_OB = OB_aux;
        }
        sum_OB += OB_aux;
    }
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC / n_elems;

    ptime->time = time;
    ptime->average_ob = (double)sum_OB / (double)n_elems;
    ptime->max_ob = max_OB;
    ptime->min_ob = min_OB;
    ptime->N = N;
    ptime->n_elems = n_elems;

    free_dictionary(dict);
    free(perm);
    free(keys);
    return OK;
}

/**
 * @brief Automatiza la toma de tiempos, llamando a generate_search_time
 * con un tamaño variable que va incrementando, guarda todos los tiempos en 
 * dentro de un archivo
 * 
 * @param method Método de ordenación
 * @param generator Función que genera las claves
 * @param order Si se usan las tablas ordeandas en el TAD diccionario
 * @param file Archivo donde se guardan los tiempos
 * @param num_min Tamaño mínimo por el que se empieza a tomar tiempos
 * @param num_max Tamaño en el que se finaliza la toma de tiempos
 * @param incr Incremento de tamaño en cada iteración
 * @param n_times Número de veces que se busca cada clave en el diccionario
 */
short generate_search_times(pfunc_search method, pfunc_key_generator generator,
                            int order, char *file, int num_min, int num_max, int incr, int n_times)
{
    int i, n_intervals, N;
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


