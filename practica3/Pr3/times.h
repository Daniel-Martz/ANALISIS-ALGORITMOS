/**
 *
 * Descripcion: Headers for time measurement functions
 *
 * Fichero: times.h
 * Autor: Daniel Martínez y Rodrigo Díaz-Regañón
 * Version: 1.0
 * Fecha: 23-11-2025
 *
 */

#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "permutations.h"  

typedef struct time_aa
{
    int N;             /* size of each element */
    int n_elems;       /* number of elements to average */
    double time;       /* average clock time */
    double average_ob; /* average number of times that the OB is executed */
    int min_ob;        /* minimum of executions of the OB */
    int max_ob;        /* maximum of executions of the OB */
} TIME_AA, *PTIME_AA;

short generate_search_times(pfunc_search method, pfunc_key_generator generator,
                            int order, char *file,
                            int num_min, int num_max,
                            int incr, int n_times);

/**
 * @brief funcion que rellena todos los campos de la estructura TIMEAA:
 * - numero de permetucianos
 * - numero de elementos por permutacion
 * - tiempo medio en segundos
 * - numero medio de OBs
 * - numero minimo de OBs
 * - numero maximo de OBs
 * @param metodo metodo de ordenacion
 * @param generator funcion que genera las claves
 * @param order si se usan las tablas ordeandas en el TAD diccionario
 * @param N tamaño del diccionario
 * @param n_times numero de veces que se busca cada N clave en el diccionario
 * @param ptime 
 * @return OK si todo fue bien, ERR si hay algun fallo
 */
short average_search_time(pfunc_search metodo, pfunc_key_generator generator,
                          int order,
                          int N,
                          int n_times,
                          PTIME_AA ptime);
