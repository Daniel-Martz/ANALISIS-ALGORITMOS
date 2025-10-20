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
    fprintf(stderr, "El primer indice tiene que ser mayor que el ultimo.\n");
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
    if (j >= ip) OB++;
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
    fprintf(stderr, "El primer indice tiene que ser mayor que el ultimo.\n");
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
