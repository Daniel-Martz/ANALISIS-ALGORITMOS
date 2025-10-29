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
#include "sorting.h"
#include "permutations.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo,
                           int n_perms,
                           int N,
                           PTIME_AA ptime)
{
  int i, max_OB = -1, min_OB = -1, OB_aux, **array_perms;
  double sum_OB = 0;
  clock_t start, end;

  if (metodo == NULL || ptime == NULL || n_perms <= 0 || N <= 0)
  {
    fprintf(stderr, "Las variables introducidas no son válidas.");
    return ERR;
  }

  ptime->n_elems = n_perms;
  ptime->N = N;

  array_perms = generate_permutations(n_perms, N);
  if (array_perms == NULL)
  {
    return ERR;
  }
  start = clock();
  for (i = 0; i < n_perms; i++)
  {

    OB_aux = metodo(array_perms[i], 0, N - 1);

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

    free(array_perms[i]);
  }
  end = clock();
  ptime->average_ob = sum_OB / n_perms;
  ptime->max_ob = max_OB;
  ptime->min_ob = min_OB;
  ptime->time = (double)(end - start) / CLOCKS_PER_SEC;
  free(array_perms);
  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char *file,
                             int num_min, int num_max,
                             int incr, int n_perms)
{
  int i, n_times;
  PTIME_AA ptime = NULL;

  if (!method || num_min <= 0 || num_max < num_min || incr <= 0)
  {
    fprintf(stderr, "Las variables introducidas no son válidas.\n");
    return ERR;
  }

  n_times = ((num_max - num_min) / incr) + 1;

  if (!(ptime = (PTIME_AA)calloc(n_times, sizeof(TIME_AA))))
  {
    fprintf(stderr, "Error al reservar memoria para la estructura del tiempo.\n");
    return ERR;
  }
  for (i = 0; i < n_times; i++)
  {
    int N = num_min + i * incr;
    if (average_sorting_time(method, n_perms, N, &ptime[i]) == ERR)
    {
      free(ptime);
      return ERR;
    }
  }
  if (save_time_table(file, ptime, n_times) == ERR)
  {
    free(ptime);
    return ERR;
  }

  free(ptime);
  return OK;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char *file, PTIME_AA ptime, int n_times)
{
  FILE *fout = NULL;
  int i;

  if (!ptime || n_times <= 0 || !file)
  {
    fprintf(stderr, "Las variables introducidas no son válidas.");
    return ERR;
  }

  if (!(fout = fopen(file, "w")))
  {
    fprintf(stderr, "Error al abrir el fichero");
    return ERR;
  }

  fprintf(fout, "%-6s %-12s %-14s %-8s %-8s\n", "N", "Time", "Average_OB", "Max_OB", "Min_OB");

  for (i = 0; i < n_times; i++)
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
