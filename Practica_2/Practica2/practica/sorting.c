/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

int merge(int *tabla, int ip, int iu, int imedio);
int partition(int *tabla, int ip, int iu, int *pos);
int median(int *tabla, int ip, int iu, int *pos);
int median_avg(int *tabla, int ip, int iu, int *pos);
int median_stat(int *tabla, int ip, int iu, int *pos);


/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int InsertSort(int *array, int ip, int iu)
{
  int i, j, OB = 0, aux;

  if (array == NULL)
  {
    fprintf(stderr, "El array es invalido.\n");
    return ERR;
  }
  if (ip < 0 || iu < 0)
  {
    fprintf(stderr, "Los indices tienen que ser positivos.");
    return ERR;
  }
  if (ip > iu)
  {
    fprintf(stderr, "El primer indice es mayor que el ultimo.\n");
    return ERR;
  }

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
    if (j >= ip)
      OB++;
    array[j + 1] = aux;
  }

  return OB;
}

/***************************************************/
/* Function: SelectSort    Date: 25/09/2025        */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int *array, int ip, int iu)
{
  int flag = 1;
  int i = iu;
  int j = 0;
  int aux = 0;
  int OB = 0;

  if (array == NULL)
  {
    fprintf(stderr, "El array es invalido.\n");
    return ERR;
  }
  if (ip < 0 || iu < 0)
  {
    fprintf(stderr, "Los indices tienen que ser positivos.");
    return ERR;
  }
  if (ip > iu)
  {
    fprintf(stderr, "El primer indice es mayor que el ultimo.\n");
    return ERR;
  }

  while ((flag == 1) && (i > ip))
  {
    flag = 0;
    for (j = ip; j < i; j++)
    {
      if (array[j] > array[j + 1])
      {
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
/* Function: Mergesort    Date: 23/10/2025         */
/* Your comment                                    */
/***************************************************/


int merge(int *tabla, int ip, int iu, int imedio)
{
  int *tabla_aux = NULL;
  int i, j, k, OB = 0;

  tabla_aux = (int *)calloc((iu - ip + 1), sizeof(int));
  if (tabla_aux == NULL)
  {
    fprintf(stderr, "Error al reservar memoria.\n");
    return ERR;
  }

  i = ip;
  j = imedio + 1;
  k = 0;/*Porque la tabla auxiliar siempre empieza por 0*/

  while (i <= imedio && j <= iu)
  {
    if (tabla[i] < tabla[j])
    {
      tabla_aux[k] = tabla[i];
      i++;
    }
    else
    {
      tabla_aux[k] = tabla[j];
      j++;
    }
    k++;
    OB++;
  }

  if (i > imedio)
  {
    while (j <= iu)
    {
      tabla_aux[k] = tabla[j];
      k++;
      j++;
    }
  }
  else if (j > iu)
  {
    while (i <= imedio)
    {
      tabla_aux[k] = tabla[i];
      i++;
      k++;
    }
  }
  for (i = ip; i <= iu; i++){
    tabla[i] = tabla_aux[i - ip];
  }
  
  free(tabla_aux);
  return OB;
}

int Mergesort(int *array, int ip, int iu)
{
  int p_medio;
  int OB_1, OB_2, OB_3, OB;

  if (array == NULL)
  {
    fprintf(stderr, "El array es invalido.\n");
    return ERR;
  }
  if (ip < 0 || iu < 0)
  {
    fprintf(stderr, "Los indices tienen que ser positivos.");
    return ERR;
  }
  if (ip > iu)
  {
    fprintf(stderr, "El primer indice es mayor que el ultimo.\n");
    return ERR;
  }

  if (ip == iu)
  {
    return 0;
  }

  p_medio = (ip + iu) / 2;/* Punto medio como función suelo*/

  OB_1 = Mergesort(array, ip, p_medio);
  if (OB_1 == ERR)
    return ERR;

  OB_2 = Mergesort(array, p_medio + 1, iu);
  if (OB_2 == ERR)
    return ERR;

  OB_3 = merge(array, ip, iu, p_medio);
  if (OB_3 == ERR)
    return ERR;

  OB = OB_1 + OB_2 + OB_3; /*Se termina sumando cada una de las OBs hechas por rutina*/
  return OB;
}

int quicksort(int *tabla, int ip, int iu)
{
  int m, ob1 = 0, ob2 = 0, ob3 = 0, ob;
  int *pos = NULL;

  if (tabla == NULL)
  {
    fprintf(stderr, "El array es invalido.\n");
    return ERR;
  }
  if (ip < 0 || iu < 0)
  {
    fprintf(stderr, "Los indices tienen que ser positivos.");
    return ERR;
  }
  if (ip > iu)
  {
    fprintf(stderr, "El primer indice es mayor que el ultimo.\n");
    return ERR;
  }

  if (ip == iu)
  {
    return 0;
  }

  if (!(pos = (int *)calloc(1, sizeof(int))))
  {
    fprintf(stderr, "Fallo reservando memoria para la variable pos.\n");
    return ERR;
  }
  ob1 = partition(tabla, ip, iu, pos);
  if (ob1 == ERR)
  {
    fprintf(stderr, "Fallo en la rutina Partir\n");
    return ERR;
  }
  m = *pos;
  if (ip < m - 1)
  {
    ob2 = quicksort(tabla, ip, m - 1);
    if (ob2 == ERR)
    {
      return ERR;
    }
  }
  if (m + 1 < iu)
  {
    ob3 = quicksort(tabla, m + 1, iu);
    if (ob3 == ERR)
    {
      return ERR;
    }
  }
  ob = ob1+ob2+ob3; /*Se termina sumando cada una de las OBs hechas por rutina*/
  free(pos);
  return ob;
}




int partition(int *tabla, int ip, int iu, int *pos)
{
  int m, ob = 0;
  int k, aux, i;

  if (!tabla || iu < ip || !pos)
  {
    return ERR;
  }

  ob=median(tabla, ip, iu, pos);
  if (ob == ERR)
  {
    return ERR;
  }
  m = *pos;
  k = tabla[m];
  aux = tabla[m];/*Guardamos el dato de la posición a pivotar*/
  tabla[m] = tabla[ip];
  tabla[ip] = aux;
  m = ip;
  for (i = ip + 1; i <= iu; i++)
  {
    if (tabla[i] < k)
    {
      m++;
      aux = tabla[m];
      tabla[m] = tabla[i];
      tabla[i] = aux;
    }
    ob++;/*Por cada if se hace una comparación de claves*/
  }
  aux = tabla[m];
  tabla[m] = tabla[ip];
  tabla[ip] = aux;
  *pos = m;
  return ob;
}

int median(int *tabla, int ip, int iu, int *pos)
{
  if (!tabla || iu < ip || !pos){
    fprintf(stderr, "Fallo en la rutina median\n");
    return ERR;
  }
  /*Elección del pivote*/
  *pos = ip;
  return 0;
}

int median_avg(int *tabla, int ip, int iu, int *pos)
{
  if (!tabla || iu < ip || !pos){
    fprintf(stderr, "Fallo en la rutina median_avg\n");
    return ERR;
  }
  /*Elección del pivote*/
  *pos = (ip + iu)/2;
  return 0;
}

int median_stat(int *tabla, int ip, int iu, int *pos)
{
  int im;
  int a;
  int b;
  int c;
  int OB = 0;
  if (!tabla || iu < ip || !pos){
    fprintf(stderr, "Fallo en la rutina median_stat\n");
    return ERR;
  }
  
  im = (ip + iu) / 2;
  a = tabla[ip];
  b = tabla[im];
  c = tabla[iu];
    /* Determinación de la mediana usando como máximo 3 comparaciones.
       Esta secuencia asegura que en todas las combinaciones
       devolvemos la posición que contiene el valor intermedio. */
  OB++;
  if (a < b) {
      OB++;
      if (b < c) {
        *pos = im;        /* a < b < c  -> b es mediana */
      } 
      else { /* b >= c */
        OB++;
        if (a < c)
          *pos = iu;    /* a < c <= b -> c es mediana */
        else
          *pos = ip;    /* c <= a < b -> a es mediana */
      }
    } 
    else { /* a >= b */
      OB++;
      if (a < c) {
        *pos = ip;        /* b <= a < c -> a es mediana */
      } 
      else { /* a >= c */
        OB++;
        if (b < c)
          *pos = iu;    /* b < c <= a -> c es mediana */
        else
          *pos = im;    /* c <= b <= a -> b es mediana */
      }
    }
  return OB;
}
