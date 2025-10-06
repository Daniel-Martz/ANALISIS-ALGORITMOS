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

typedef struct time_aa
{
  int N;             // Input size
  int n_elems;       // total number of elements to be averaged
  double time;       // average clock time
  double average_ob; // avergae number of times the OB is executed
  int min_ob;        // minimum number of OB executions
  int max_ob;        // maximum number of OB executions
} TIME_AA, *PTIME_AA;

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
  ptime->time = end - start /CLOCKS_PER_SEC;
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
  FILE *fout = NULL;
  int i;
  PTIME_AA ptime = NULL;

  if (!method || !fout || num_min <= 0 || num_max < num_min)
  {
    return ERR;
  }

  if (!(fout = fopen(file, "w")))
  {
    return ERR;
  }

  if (!(ptime = (PTIME_AA)calloc(1, sizeof(TIME_AA))))
  {
    return ERR;
  }

  for (i = num_min; i <= num_max; i += incr)
  {
    if (average_sorting_time(method, n_perms, i, ptime) == ERR)
    {
      return ERR;
    }
    fprintf(fout, "Tamaño de la permutacion: %i elementos | Tiempo medio:%lf segundos | Numero promedio de OB realizadas:%lf | Numero minimo de OB realizadas:%i | Numero maximo de OB realizadas:%i\n", i, ptime->time, ptime->average_ob, ptime->min_ob, ptime->max_ob);
  }

  fclose(fout);
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

  if(!ptime || n_times<=0 || !file){
    return ERR;
  }

  if(!(file = fopen(file,"w"))){
    return ERR;
  }

  fprintf(fout, "|\tN\t|\ttime\t|\taverage_ob\t|\tmax_ob\t|\tmin_ob\t|");
  for(i=0; i<n_times;i++){
    fprintf(fout, "|\t%i\t|\t%lf\t|\t%lf\t|\t%i\t|\t%i\t|", ptime[i].N, ptime[i].time,ptime[i].average_ob,ptime[i].max_ob, ptime[i].min_ob);
  }
  fclose(file);
  return OK;
}
